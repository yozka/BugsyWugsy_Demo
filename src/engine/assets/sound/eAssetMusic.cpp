//◦ EggEngine ◦
#include "eAssetMusic.h"
#include "engine/CoreSDL.h"


namespace Engine::Assets
{

	EAssetMusic::EAssetMusic()
	{
	}


	EAssetMusic::~EAssetMusic()
	{
		if (m_music) {
			Mix_FreeMusic(m_music);
			m_music = {};
		}
	}


	EAssetMusic::UPtr EAssetMusic::Create(const std::string& name, const std::string& group, const std::vector<char>& data)
	{
		auto asset = std::make_unique<EAssetMusic>();
		asset->m_name = name;
		asset->m_group = group;
		asset->m_data = data;

		auto rw = SDL_RWFromMem(asset->m_data.data(), static_cast<int>(asset->m_data.size()));
		if (rw == nullptr) {
			return {};
		}
		asset->m_music = Mix_LoadMUSType_RW(rw, MUS_NONE, 1);
		if (asset->m_music == nullptr) {
			return {};
		}
		return asset;
	}


	std::string EAssetMusic::Name() const
	{
		return m_name;
	}


	std::string EAssetMusic::Group() const
	{
		return m_group;
	}

}
