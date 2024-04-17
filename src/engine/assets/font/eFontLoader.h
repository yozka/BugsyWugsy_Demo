//◦ EggEngine ◦
#pragma once
#include <string>

#include "eAssetFont.h"
#include "engine/assets/eAssetResources.h"

namespace Engine::Assets
{

	class EFontLoader
	{
	public:
		using Ptr = std::shared_ptr<EFontLoader>;
		using UPtr = std::unique_ptr<EFontLoader>;
		
	public:
		EFontLoader(const EAssetResources::Ptr& resources);
		virtual ~EFontLoader() = default;
	
	public:
		bool LoadFonts(const std::string &fileName);
		EAssetFont::Ptr LoadFont(const std::string& group, const std::string& name, const int fontSize, const std::string& fileName = "");

	private:
		EAssetResources::Ptr m_resources = {};
		
	};

}
