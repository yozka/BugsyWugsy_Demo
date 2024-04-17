//◦ EggEngine ◦
#include "eTextureLoader.h"
#include "eAssetTexture.h"
#include "eAssetSubTexture.h"
#include "engine/files/os/eOS.h"
#include "engine/xml/eTinyxml.h"

namespace Engine::Assets
{
	
	ETextureLoader::ETextureLoader(const EAssetResources::Ptr& resources)
		:
			m_resources(resources)
	{
		
	}


	EAssetSprite::Ptr ETextureLoader::LoadSprite(const std::string& group, const std::string& spriteName, const std::string &fileName)
	{
		auto texture = LoadTexture(spriteName, group, fileName.empty() ? spriteName : fileName);
		return texture;
	}


	bool ETextureLoader::LoadSprites(const std::string &fileName)
	{
		auto file = Engine::Files::OS::Open(fileName);
		if (!file) return false;

		auto doc = Engine::Xml::Load(file);
		file->Close();

		auto root = doc->RootElement();
		if (!root) return false;
		auto node = root->FirstChildElement("sprite");
		while (node) {
			const std::string spriteName 	= node->Attribute("name");
			const std::string group 		= node->Attribute("group");
			const std::string imagePath 	= node->Attribute("imagePath");
			LoadTexture(spriteName, group, imagePath);

			node = node->NextSiblingElement("sprite");
		}
		return true;
	}


	bool ETextureLoader::LoadAtlas(const std::string& fileName)
	{
		auto file = Engine::Files::OS::Open(fileName);
		if (!file) return false;

		auto doc = Engine::Xml::Load(file);
		file->Close();

		auto root = doc->RootElement();
		if (!root) return false;
		auto node = root->FirstChildElement("atlas");
		while (node) {
			const std::string group = node->Attribute("group");
			const std::string imagePath = node->Attribute("imagePath");
			if (auto atlas = LoadTexture("atlas:/"+imagePath, group, imagePath)) {
				//
				auto sub = node->FirstChildElement("SubTexture");
				while (sub) {
					const std::string spriteName = sub->Attribute("name");
					const int x = sub->IntAttribute("x");
					const int y = sub->IntAttribute("y");
					const int width = sub->IntAttribute("width");
					const int height = sub->IntAttribute("height");
					
					AddSubTexture(atlas, spriteName, x, y, width, height);
					
					sub = sub->NextSiblingElement("SubTexture");
				}
				//
			}
			node = node->NextSiblingElement("atlas");
		}
		return true;
	}


	EAssetSprite::Ptr ETextureLoader::LoadTexture(const std::string& name, const std::string& group, const std::string &fileName)
	{
		EAssetSprite::Ptr texture = {};
		if (const auto file = Engine::Files::OS::Open(fileName)) {

			//Загружаем данные из файла
			const auto fileSize = file->Size();
			std::vector<char> dataImage(fileSize);
			if (file->Read(dataImage.data(), fileSize) != fileSize) {
				file->Close();
				return {};
			}
			//
			
			texture = EAssetTexture::Create(name, group, dataImage);
			if (texture) {
				m_resources->Add<EAssetSprite>(texture);
			}
			file->Close();
		}
		return texture;
	}


	void ETextureLoader::AddSubTexture(const EAssetSprite::Ptr& atlas, const std::string& name,
									   const int x, const int y,
									   const int width, const int height)
	{
		EAssetSprite::Ptr texture = EAssetSubTexture::Create(name, atlas, IRect(x, y, x + width, y + height));
		if (texture) {
			m_resources->Add<EAssetSprite>(texture);
		}
	}

}
