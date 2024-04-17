//◦ EggEngine ◦
#include "eAssetSample.h"
#include "engine/CoreSDL.h"
#include "engine/debug/eAssert.h"

namespace Engine::Assets
{

	EAssetSample::EAssetSample()
	{
	}


	EAssetSample::~EAssetSample()
	{
		if (m_sound) {
			Mix_FreeChunk(m_sound);
			m_sound = {};
		}
	}


	EAssetSample::UPtr EAssetSample::Create(const std::string& name, const std::string& group, const std::vector<char>& data)
	{
		auto asset = std::make_unique<EAssetSample>();
		asset->m_name = name;
		asset->m_group = group;
		asset->m_data = data;

		auto rw = SDL_RWFromMem(asset->m_data.data(), static_cast<int>(asset->m_data.size()));
		if (rw == nullptr) {
			sassert2(false, "Звуковой файл отсутствует в пямяти");
			return {};
		}
		asset->m_sound = Mix_LoadWAV_RW(rw, 1);
		if (asset->m_sound == nullptr) {
			sassert2(false, "Звуковой файл не инцеализирован из памяти");
			return {};
		}
		return asset;
	}


	std::string EAssetSample::Name() const
	{
		return m_name;
	}


	std::string EAssetSample::Group() const
	{
		return m_group;
	}

}
