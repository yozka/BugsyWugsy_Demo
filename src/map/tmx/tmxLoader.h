//◦ EggEngine ◦
#pragma once
#include <string>
#include <utility>
#include <map>
#include <vector>
#include <functional>

#include "map/GameMap.h"
#include "engine/assets/eAssetResources.h"
#include "engine/xml/eTinyxml.h"
#include "engine/common/eProperty.h"

namespace Game::Map::Tmx
{

	//Загрузка игровой карты
	class ATmxLoader
	{
	public:
		using UPtr		= std::unique_ptr<ATmxLoader>;
		using Ptr		= std::shared_ptr<ATmxLoader>;
		using WeakPtr	= std::weak_ptr<ATmxLoader>;

		using FactoryObject =  std::function<Game::AGameObject::UPtr(const Engine::Property& prop)>;
		
	public:
		ATmxLoader(const Engine::Assets::EAssetResources::Ptr& resources, const FactoryObject &factory);
		virtual ~ATmxLoader();
		
	public:
		Game::Map::AGameMap::UPtr Load(const std::string &group, const std::string &fileName);

	private:
		void LoadTilesets	(const std::string &path, Engine::Xml::Node *root);
		void LoadTileset	(const std::string &fileName, const int firstgid);
		void LoadLayers		(Engine::Xml::Node *root);
		void LoadLayer		(Engine::Xml::Node *node);
		void LoadObjects	(Engine::Xml::Node *node);
		void LoadGrid		(Engine::Xml::Node *node);

		void LoadProperties(Engine::Xml::Node *node, Engine::Property &prop);
		void LoadAttributes(Engine::Xml::Node *node, Engine::Property &prop);
		
	private:
		Engine::Assets::EAssetResources::Ptr m_resources;
		FactoryObject m_factory;
		
		Game::Map::AGameMap::UPtr m_map;
		std::string m_group;
		
		int m_map_width 	= {};
		int m_map_height 	= {};
		int m_map_tilewidth	= {};
		int m_map_tileheight= {};

		//Привязка тайла к колизии
		std::map<int, EGridType> m_tilesGround;
		
		//Привязка тайла к анимации
		std::map<int, std::string> m_tilesAnimation;
		std::map<std::string, std::vector<std::pair<int,float>>> m_animations; //Анимированные тайлы
		
	};

}
