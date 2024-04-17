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
	 * Звуковой файл
	 */

	class EAssetSample : public EAsset
	{
	public:
		using Ptr = std::shared_ptr<EAssetSample>;
		using UPtr = std::unique_ptr<EAssetSample>;
		
	public:
		EAssetSample();
		~EAssetSample() override;
		
	public:
		static EAssetSample::UPtr Create(const std::string& name, const std::string& group, const std::vector<char>& data);

	public:
		std::string Name() const override;
		std::string Group() const override; //Группа ассета
		
	public:
		Mix_Chunk* GetSample() const { return m_sound; }
		
	private:
		std::string	m_name;
		std::string	m_group;

		std::vector<char> m_data;
		Mix_Chunk* m_sound = {};

	};

}
