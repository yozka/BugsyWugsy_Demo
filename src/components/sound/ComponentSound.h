//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <map>

#include "engine/CoreSDL.h"
#include "engine/assets/sound/eAssetMusic.h"
#include "engine/assets/sound/eAssetSample.h"

#include "components/Component.h"

namespace Game::Components
{

	//Компанент для проигрывания звуков
	class AComponentSound : public AComponent
	{
	public:
		using UPtr		= std::unique_ptr<AComponentSound>;
		using Ptr		= std::shared_ptr<AComponentSound>;
		using WeakPtr	= std::weak_ptr<AComponentSound>;

	public:
		AComponentSound();
		~AComponentSound() override;
		
	public:
		void Destroy() override;
		
	public:
		void AppendSample(const std::string &name, Engine::Assets::EAssetSample::Ptr sample);
		void Play(const std::string &name);
		
	private:
		std::map<std::string, Engine::Assets::EAssetSample::Ptr> m_samples;
		
	};

}
