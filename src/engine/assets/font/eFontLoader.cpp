//◦ EggEngine ◦
#include "eFontLoader.h"
#include "engine/files/os/eOS.h"
#include "engine/xml/eTinyxml.h"

namespace Engine::Assets
{
	
	EFontLoader::EFontLoader(const EAssetResources::Ptr& resources)
		:
			m_resources(resources)
	{
		
	}


	bool EFontLoader::LoadFonts(const std::string &fileName)
	{
		auto file = Engine::Files::OS::Open(fileName);
		if (!file) return false;

		auto doc = Engine::Xml::Load(file);
		file->Close();

		auto root = doc->RootElement();
		if (!root) return false;
		auto node = root->FirstChildElement("font");
		while (node) {
			const std::string fontName 		= node->Attribute("name");
			const std::string group 		= node->Attribute("group");
			const std::string fontPath 		= node->Attribute("fontPath");
			const int fontSize				= node->IntAttribute("ptsize");
			LoadFont(group, fontName, fontSize, fontPath);

			node = node->NextSiblingElement("font");
		}
		return true;
	}


	EAssetFont::Ptr EFontLoader::LoadFont(const std::string& group, const std::string& name, const int fontSize, const std::string& fileName)
	{
		EAssetFont::Ptr font = {};
		if (const auto file = Engine::Files::OS::Open(fileName.empty() ? name : fileName)) {

			//Загружаем данные из файла
			const auto fileSize = file->Size();
			std::vector<char> dataFont(fileSize);
			if (file->Read(dataFont.data(), fileSize) != fileSize) {
				file->Close();
				return {};
			}
			//
			
			font = EAssetFont::Create(name, group, fontSize, dataFont);
			if (font) {
				m_resources->Add<EAssetFont>(font);
			}
			file->Close();
		}
		return font;
	}



	
}
