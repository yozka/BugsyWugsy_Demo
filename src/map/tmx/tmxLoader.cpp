//◦ EggEngine ◦
#include "tmxLoader.h"
#include "engine/files/eDir.h"
#include "engine/files/os/eOS.h"
#include "engine/xml/eTinyxml.h"
#include "engine/assets/texture/eTextureLoader.h"
#include "engine/assets/texture/eAssetSprite.h"
#include "engine/assets/texture/eAssetSubTexture.h"
#include "engine/common/eUtils.h"

#include "map/tileset/Tileset.h"
#include "map/layers/tiles/LayerTiles.h"

#include "components/grid/ComponentGrid.h"
#include "components/layer/ComponentLayer.h"
#include "components/tilesets/ComponentTilesets.h"


using namespace Game::Map::Tmx;


ATmxLoader::ATmxLoader(const Engine::Assets::EAssetResources::Ptr& resources, const FactoryObject &factory)
	:
		m_resources(resources),
		m_factory(factory)
{

}


ATmxLoader::~ATmxLoader()
{

}


Game::Map::AGameMap::UPtr ATmxLoader::Load(const std::string &group, const std::string &fileName)
{
	auto file = Engine::Files::OS::Open(fileName);
	sassert(file);
	if (!file) return {};
	auto doc = Engine::Xml::Load(file);
	file->Close();

	auto root = doc->RootElement();
	sassert(root);
	if (!root) return {};

	m_group = group;

	m_map_width 		= root->IntAttribute("width");
	m_map_height 		= root->IntAttribute("height");
	m_map_tilewidth 	= root->IntAttribute("tilewidth");
	m_map_tileheight 	= root->IntAttribute("tileheight");
	m_map = std::make_unique<Game::Map::AGameMap>(fileName, m_map_width, m_map_height, m_map_tilewidth, m_map_tileheight);
	
	LoadTilesets(Engine::Files::ExtractDirectory(fileName), root);
	LoadLayers(root);
	
	Game::Map::AGameMap::UPtr map;
	std::swap(map, m_map);
	return map;
}

void ATmxLoader::LoadTilesets(const std::string &path, Engine::Xml::Node *root)
{
	auto node = root->FirstChildElement("tileset");
	while (node) {
		const int firstgid = node->IntAttribute("firstgid");
		const std::string source = Engine::Xml::ToString(node, "source");
		sassert(!source.empty());
		LoadTileset(path + source, firstgid);
		node = node->NextSiblingElement("tileset");
	}
}

void ATmxLoader::LoadTileset(const std::string &fileName, const int firstgid)
{
	auto file = Engine::Files::OS::Open(fileName);
	sassert(file);
	if (!file) return;
	auto doc = Engine::Xml::Load(file);
	file->Close();

	auto root = doc->RootElement();
	sassert(root);
	if (!root) return;
	
	const std::string name = Engine::Xml::ToString(root, "name");
	const int tilewidth = root->IntAttribute("tilewidth");
	const int tileheight = root->IntAttribute("tileheight");
	const int tilecount = root->IntAttribute("tilecount");
	const int columns = root->IntAttribute("columns");
	auto nodeImage = root->FirstChildElement("image");
	sassert(nodeImage);
	if (!nodeImage) return;
	const std::string source = Engine::Xml::ToString(nodeImage, "source");
	
	Engine::Assets::ETextureLoader loaderTexture(m_resources);
	auto texture = loaderTexture.LoadSprite(m_group, name, Engine::Files::ExtractDirectory(fileName) + source);
	sassert(texture);
	if (!texture) return;
	
	auto tileset = ATileset::Create(name, firstgid, tilewidth, tileheight, tilecount, columns, texture);
	sassert(tileset);
	if (!tileset) return;
	
	//Загружаем параметры для тайлов
	auto nodeTile = root->FirstChildElement("tile");
	while (nodeTile) {
		const int tileId = nodeTile->IntAttribute("id");
		const int wtileId = firstgid + tileId;
		Engine::Property prop;
		LoadProperties(nodeTile, prop);
		if (prop.Contains("name")) {
			//Отдельные спрайты зарегестрируем в ресурсх для доступа из игры
			const int x = (tileId % columns) * tilewidth;
			const int y = (tileId / columns) * tileheight;
			const auto subname = prop.GetString("name");
			auto subtexture = Engine::Assets::EAssetSubTexture::Create(subname, texture, Engine::IRect(x+1, y+1, x + tilewidth, y + tileheight));
			m_resources->Add<Engine::Assets::EAssetSprite>(std::move(subtexture));
			
			//Также отдельные спрайты зарегиструем в системе
			tileset->AppendTile(subname, tileId);
		}
		
		//тип тайлов для построения карты проходимости
		if (prop.GetBool("ground_block"))		{ m_tilesGround[wtileId] = EGridType::block; }
		if (prop.GetBool("ground_passable"))	{ m_tilesGround[wtileId] = EGridType::passable; }
		if (prop.GetBool("ground_road"))		{ m_tilesGround[wtileId] = EGridType::road; }
		if (prop.GetBool("ground_water"))		{ m_tilesGround[wtileId] = EGridType::water; }
		
		//анимация тайлов
		if (prop.Contains("animation")) {
			const auto nameAnimation = prop.GetString("animation");
			const auto animationTime = prop.GetFloat("animationTime", 0.5f);
			m_tilesAnimation[wtileId] = nameAnimation;
			m_animations[nameAnimation].push_back({wtileId, animationTime});
		}
		
		nodeTile = nodeTile->NextSiblingElement("tile");
	}
	
	if (m_map) {
		m_map->AppendTileset(std::move(tileset));
	}
}

void ATmxLoader::LoadLayers(Engine::Xml::Node *root)
{
	auto node = root->FirstChild();
	while (node) {
		auto layer = node->ToElement();
		const std::string type = node->Value();
		const std::string classname = Engine::Xml::ToString(layer, "class");
		if (type == "layer" && classname == "ALayerTiles") {
			LoadLayer(layer);
		}
		if (type == "objectgroup" && classname == "ALayerObjects") {
			LoadObjects(layer);
		}
		if (type == "layer" && classname == "AGrigCollision") {
			LoadGrid(layer);
		}
		node = node->NextSibling();
	}
}

void ATmxLoader::LoadLayer(Engine::Xml::Node *node)
{
	const std::string name = Engine::Xml::ToString(node, "name");
	const int width = node->IntAttribute("width");
	const int height = node->IntAttribute("height");

	auto layer = std::make_shared<Game::Map::ALayerTiles>(name, width, height);
	auto ndata = node->FirstChildElement("data");
	sassert(ndata);
	if (!ndata) return;
	if (const std::string encoding = Engine::Xml::ToString(ndata, "encoding"); encoding != "csv") {
		sassert(false);
		return;
	}
	const auto data = Engine::Split(Engine::Remove(ndata->GetText(), '\n'), ',');
	sassert(data.size() == width * height);
	int x = 0;
	int y = 0;
	for (const auto tileId : data) {
		const int wtileId = Engine::StringToInt(tileId);
		layer->SetTileId(x, y, wtileId);
		
		//анимация тайлов
		const auto it = m_tilesAnimation.find(wtileId);
		if (it != m_tilesAnimation.end()) {
			const auto nameAnimation = it->second;
			for (auto data : m_animations[nameAnimation]) {
				layer->AppendAnimation(x, y, data.first, data.second);
			}
		}
		
		//
		x++;
		if (x == width) {
			x = 0;
			y++;
		}
	}
	
	if (m_map) {
		m_map->AppendLayer(layer);
	}
}


void ATmxLoader::LoadObjects(Engine::Xml::Node *node)
{
	if (!m_factory) return;
	
	const std::string name = Engine::Xml::ToString(node, "name");
	auto layer = std::make_shared<Game::Map::ALayerRenderObjects>(name);
	auto nodeObj = node->FirstChildElement("object");
	while (nodeObj) {
		const auto objType = Engine::Xml::ToString(nodeObj, "type");
		if (objType == "AGameObject") {
			Engine::Property prop;
			LoadAttributes(nodeObj, prop);
			LoadProperties(nodeObj, prop);
			if (AGameObject::Ptr obj = m_factory(prop)) {
				if (prop.GetBool("AA_Rendering")) {
					layer->Append(obj);
				}
				if (prop.GetBool("AA_GameLogic") && m_map) {
					m_map->AppendObject(obj);
				}
				
				//Дополнительные компаненты
				//У объекта есть доступ к сетке коллизий
				if (prop.GetBool("AComponentGrid")) {
					obj->CreateComponent<Components::AComponentGrid>(m_map->grid);
				}
				
				//Объект хочет доступ к иговой логике
				if (prop.GetBool("AComponentLayer")) {
					obj->CreateComponent<Components::AComponentLayer>(m_map->layers, layer, m_map->logic);
				}
				
				//объект доступ к тайлсетам
				if (prop.GetBool("AComponentTilesets")) {
					obj->CreateComponent<Components::AComponentTilesets>(m_map->tilesets);
				}
				
			}
		}
		nodeObj = nodeObj->NextSiblingElement("object");
	}
	if (m_map) {
		m_map->AppendLayer(layer);
	}
}

void ATmxLoader::LoadGrid(Engine::Xml::Node *node)
{
	if (!m_map) return;
	
	const int width = node->IntAttribute("width");
	const int height = node->IntAttribute("height");

	auto ndata = node->FirstChildElement("data");
	sassert(ndata);
	if (!ndata) return;
	if (const std::string encoding = Engine::Xml::ToString(ndata, "encoding"); encoding != "csv") {
		sassert(false);
		return;
	}
	const auto data = Engine::Split(Engine::Remove(ndata->GetText(), '\n'), ',');
	sassert(data.size() == width * height);
	int x = 0;
	int y = 0;
	for (const auto tileId : data) {
		const int id = Engine::StringToInt(tileId);
		if (id > 0) {
			const auto it = m_tilesGround.find(id);
			sassert(it != m_tilesGround.end());
			if (it != m_tilesGround.end()) {
				m_map->SetGrid({x, y}, it->second);
			}
		}
		
		x++;
		if (x == width) {
			x = 0;
			y++;
		}
	}
}


void ATmxLoader::LoadProperties(Engine::Xml::Node *node, Engine::Property &prop)
{
	if (!node) return;
	auto p = node->FirstChildElement("properties");
	if (!p) return;
	p = p->FirstChildElement("property");
	while(p) {
		const auto name = Engine::Xml::ToString(p, "name");
		const auto type = Engine::Xml::ToString(p, "type");
		if (type.empty()) 		prop[name] = { Engine::Xml::ToString	(p, "value") };
		if (type == "bool")		prop[name] = { Engine::Xml::ToBool		(p, "value") };
		if (type == "float")	prop[name] = { Engine::Xml::ToFloat		(p, "value") };
		if (type == "int")		prop[name] = { Engine::Xml::ToInteger	(p, "value") };

		p = p->NextSiblingElement("property");
	}
}


void ATmxLoader::LoadAttributes(Engine::Xml::Node *node, Engine::Property &prop)
{
	if (Engine::Xml::Contain(node, "name"))		prop["name"] = 		{ Engine::Xml::ToString(node, "name") };
	if (Engine::Xml::Contain(node, "x"))		prop["x"] =			{ Engine::Xml::ToFloat(node, "x") };
	if (Engine::Xml::Contain(node, "y"))		prop["y"] =			{ Engine::Xml::ToFloat(node, "y") };
	if (Engine::Xml::Contain(node, "width"))	prop["width"] =		{ Engine::Xml::ToFloat(node, "width") };
	if (Engine::Xml::Contain(node, "height"))	prop["height"] =	{ Engine::Xml::ToFloat(node, "height") };
	
	prop["map_group"] 		= { m_group };
	prop["map_width"] 		= { m_map_width };
	prop["map_height"] 		= { m_map_height };
	prop["map_tilewidth"] 	= { m_map_tilewidth };
	prop["map_tileheight"] 	= { m_map_tileheight };
	
}
