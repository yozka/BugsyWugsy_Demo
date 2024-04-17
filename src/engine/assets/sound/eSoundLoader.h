//◦ EggEngine ◦
#pragma once
#include <string>

#include "eAssetMusic.h"
#include "eAssetSample.h"
#include "engine/assets/eAssetResources.h"

namespace Engine::Assets
{


	class ESoundLoader
	{
	public:
		using Ptr = std::shared_ptr<ESoundLoader>;
		using UPtr = std::unique_ptr<ESoundLoader>;
		
	public:
		ESoundLoader(const EAssetResources::Ptr& resources);
		virtual ~ESoundLoader() = default;
	
	public:
		bool Load(const std::string &fileName);
		EAssetSample::Ptr LoadSample(const std::string& group, const std::string& name, const std::string& fileName = "");
		EAssetMusic::Ptr LoadMusic(const std::string& group, const std::string& name, const std::string& fileName = "");
		
	private:
		EAssetResources::Ptr m_resources = {};
		
	};

}
