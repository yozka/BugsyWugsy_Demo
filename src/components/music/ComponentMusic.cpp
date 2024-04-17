//◦ EggEngine ◦
#include "ComponentMusic.h"


using namespace Game::Components;


AComponentMusic::AComponentMusic()
{

}


AComponentMusic::~AComponentMusic()
{

}


void AComponentMusic::Destroy()
{
	m_music1 = {};
	m_music2 = {};
}


void AComponentMusic::SetMusic1(const Engine::Assets::EAssetMusic::Ptr &music)
{
	m_music1 = music;
}

void AComponentMusic::SetMusic2(const Engine::Assets::EAssetMusic::Ptr &music)
{
	m_music2 = music;
}

void AComponentMusic::SetFade(const float value)
{
	m_fade = static_cast<int>(value * 1000.0f);
	Mix_FadeOutMusic(m_fade);
}

void AComponentMusic::SetLoop(const bool value)
{
	m_loop = value;
}

void AComponentMusic::SetAutoStart(const bool value)
{
	m_autoStart = value;
}

void AComponentMusic::PlayMusic1()
{
	Mix_PlayMusic(m_music1->GetMusic(), m_loop ? -1 : 0);
}


void AComponentMusic::PlayMusic2()
{
	Mix_PlayMusic(m_music2->GetMusic(), m_loop ? -1 : 0);
}


void AComponentMusic::StopMusic()
{
	Mix_HaltMusic();
}

void AComponentMusic::Start()
{
	if (m_autoStart) {
		PlayMusic1();
	}
}
