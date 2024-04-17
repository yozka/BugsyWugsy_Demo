//◦ EggEngine ◦
#include "ComponentSound.h"


using namespace Game::Components;


AComponentSound::AComponentSound()
{

}


AComponentSound::~AComponentSound()
{

}


void AComponentSound::Destroy()
{
	m_samples.clear();
}


void AComponentSound::AppendSample(const std::string &name, Engine::Assets::EAssetSample::Ptr sample)
{
	m_samples[name] = sample;
}


void AComponentSound::Play(const std::string &name)
{
	auto it = m_samples.find(name);
	if (it != m_samples.end()) {
		auto sample = it->second->GetSample();
		Mix_PlayChannel(-1, sample, 0);
	}
}

