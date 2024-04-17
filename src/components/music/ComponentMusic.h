//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "engine/CoreSDL.h"
#include "engine/assets/sound/eAssetMusic.h"
#include "engine/assets/sound/eAssetSample.h"

#include "components/Component.h"

namespace Game::Components
{

	//Компанент для проигрывания музыки
	class AComponentMusic : public AComponent
	{
	public:
		using UPtr		= std::unique_ptr<AComponentMusic>;
		using Ptr		= std::shared_ptr<AComponentMusic>;
		using WeakPtr	= std::weak_ptr<AComponentMusic>;

	public:
		AComponentMusic();
		~AComponentMusic() override;
		
	public:
		void Start() override;
		void Destroy() override;
		
	public:
		void SetMusic1(const Engine::Assets::EAssetMusic::Ptr &music);
		void SetMusic2(const Engine::Assets::EAssetMusic::Ptr &music);
		void SetFade(const float value);
		void SetLoop(const bool value);
		void SetAutoStart(const bool value);
		
	public:
		void PlayMusic1();
		void PlayMusic2();
		
		void StopMusic();
		
	private:
		Engine::Assets::EAssetMusic::Ptr m_music1 = {};
		Engine::Assets::EAssetMusic::Ptr m_music2 = {};

		bool m_autoStart = { false };
		bool m_loop = { false };
		int m_fade = { 500 };
		
	};

}
