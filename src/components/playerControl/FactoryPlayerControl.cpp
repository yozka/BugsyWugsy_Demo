//◦ EggEngine ◦
#include "FactoryPlayerControl.h"
#include "WidgetPlayerControl.h"
#include "engine/assets/texture/eTextureLoader.h"

using namespace Game::Components;


AFactoryPlayerControl::AFactoryPlayerControl(const Engine::Assets::EAssetResources::Ptr &assets, const Map::ACamera::Ptr &camera, Engine::GUI::EWidget::Ptr *out_widget)
	:
		m_assets(assets),
		m_camera(camera),
		m_widget(out_widget)
{
}


void AFactoryPlayerControl::Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop)
{
	if (!prop.GetBool("AComponentPlayerControl")) return;
	Engine::Assets::ETextureLoader loaderTexture(m_assets);
	
	//Компанент для упраления игроком
	auto control = obj->CreateComponent<Components::AComponentPlayerControl>();
	control->SetSpeed(prop.GetFloat("Speed", 1.0f));
	control->SetPathDepth(prop.GetInteger("PathDepth", 16));
	
	//Виджет
	auto widget = std::make_shared<AWidgetPlayerControl>(m_camera, control);

	const auto pointSpriteId = prop.GetString("ControlPointSpriteID");
	if (m_assets->Contains<Engine::Assets::EAssetSprite>(pointSpriteId)) {
		widget->SetPointSprite(m_assets->Find<Engine::Assets::EAssetSprite>(pointSpriteId));
	} else {
		widget->SetPointSprite(loaderTexture.LoadSprite(prop.GetString("map_group", "level"), pointSpriteId));
	}
	
	if (m_widget) {
		*m_widget = widget;
	}
	//
}
