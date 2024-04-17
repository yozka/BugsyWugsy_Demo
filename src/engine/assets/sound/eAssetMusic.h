//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>

#include "engine/CoreSDL.h"
#include "engine/assets/eAsset.h"

namespace Engine::Assets
{
	/*
	 * Музыка
	 */

	class EAssetMusic : public EAsset
	{
	public:
		using Ptr = std::shared_ptr<EAssetMusic>;
		using UPtr = std::unique_ptr<EAssetMusic>;
		
	public:
		EAssetMusic();
		~EAssetMusic() override;
		
	public:
		static EAssetMusic::UPtr Create(const std::string& name, const std::string& group, const std::vector<char>& data);

	public:
		std::string Name() const override;
		std::string Group() const override; //Группа ассета
		
	public:
		Mix_Music* GetMusic() const { return m_music; }
		
	private:
		std::string	m_name;
		std::string	m_group;

		std::vector<char> m_data;
		Mix_Music* m_music = {};

	};

}
