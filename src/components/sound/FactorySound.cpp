//◦ EggEngine ◦
#include "FactorySound.h"
#include "engine/assets/sound/eSoundLoader.h"

using namespace Game::Components;

AFactorySound::AFactorySound(const Engine::Assets::EAssetResources::Ptr &assets)
	:
		m_assets(assets)
{
	
}


void AFactorySound::Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop)
{
	if (!prop.GetBool("AComponentSound")) return;
	
	const std::string prefix = "Sound_";
	auto sound = obj->CreateComponent<Components::AComponentSound>();
	for (const auto key : prop.Keys()) {
		const auto it = key.find(prefix);
		if (it != 0) continue;
		const auto name = key.substr(prefix.length());
		const auto fileName = prop.GetString(key);
		if (fileName.empty()) continue;
		
		if (m_assets->Contains<Engine::Assets::EAssetSample>(name)) {
			sound->AppendSample(name, m_assets->Find<Engine::Assets::EAssetSample>(name));
		} else {
			Engine::Assets::ESoundLoader loader(m_assets);
			auto sample = loader.LoadSample(prop.GetString("map_group", "level"), name, fileName);
			sound->AppendSample(name, sample);
		}
	}
	
}
