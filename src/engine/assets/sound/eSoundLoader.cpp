//◦ EggEngine ◦
#include "eSoundLoader.h"
#include "engine/files/os/eOS.h"
#include "engine/xml/eTinyxml.h"

namespace Engine::Assets
{
	
	ESoundLoader::ESoundLoader(const EAssetResources::Ptr& resources)
		:
			m_resources(resources)
	{
		
	}

	bool ESoundLoader::Load(const std::string &fileName)
	{
		auto file = Engine::Files::OS::Open(fileName);
		if (!file) return false;

		auto doc = Engine::Xml::Load(file);
		file->Close();

		auto root = doc->RootElement();
		if (!root) return false;
		auto node = root->FirstChildElement("music");
		while (node) {
			const std::string musicName 	= node->Attribute("name");
			const std::string group 		= node->Attribute("group");
			const std::string musicPath 	= node->Attribute("musicPath");
			LoadMusic(group, musicName, musicPath);

			node = node->NextSiblingElement("music");
		}
		
		node = root->FirstChildElement("sample");
		while (node) {
			const std::string sampleName 	= node->Attribute("name");
			const std::string group 		= node->Attribute("group");
			const std::string samplePath 	= node->Attribute("samplePath");
			LoadSample(group, sampleName, samplePath);

			node = node->NextSiblingElement("sample");
		}
		return true;
	}


	EAssetSample::Ptr ESoundLoader::LoadSample(const std::string& group, const std::string& name, const std::string& fileName)
	{
		EAssetSample::Ptr sample = {};
		if (const auto file = Engine::Files::OS::Open(fileName.empty() ? name : fileName)) {

			//Загружаем данные из файла
			const auto fileSize = file->Size();
			std::vector<char> dataSample(fileSize);
			if (file->Read(dataSample.data(), fileSize) != fileSize) {
				sassert2(false, "Звуковой файл не загружен");
				file->Close();
				return {};
			}
			//

			sample = EAssetSample::Create(name, group, dataSample);
			if (sample) {
				m_resources->Add<EAssetSample>(sample);
			}
			file->Close();
		}
		return sample;
	}


	EAssetMusic::Ptr ESoundLoader::LoadMusic(const std::string& group, const std::string& name, const std::string& fileName)
	{
		EAssetMusic::Ptr music = {};
		if (const auto file = Engine::Files::OS::Open(fileName.empty() ? name : fileName)) {

			//Загружаем данные из файла
			const auto fileSize = file->Size();
			std::vector<char> dataMusic(fileSize);
			if (file->Read(dataMusic.data(), fileSize) != fileSize) {
				file->Close();
				return {};
			}
			//

			music = EAssetMusic::Create(name, group, dataMusic);
			if (music) {
				m_resources->Add<EAssetMusic>(music);
			}
			file->Close();
		}
		return music;
	}




	
}
