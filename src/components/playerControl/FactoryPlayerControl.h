//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "ComponentPlayerControl.h"

#include "map/camera/Camera.h"
#include "objects/FactoryObject.h"

#include "engine/assets/eAssetResources.h"
#include "engine/gui/eWidget.h"

namespace Game::Components
{

	//Фабрика создания игрового управления
	class AFactoryPlayerControl : public AFactory
	{
	public:
		AFactoryPlayerControl(const Engine::Assets::EAssetResources::Ptr &assets, const Map::ACamera::Ptr &camera, Engine::GUI::EWidget::Ptr *out_widget);
		void Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop) override;
	
	private:
		Engine::Assets::EAssetResources::Ptr m_assets;
		Map::ACamera::Ptr m_camera;
		Engine::GUI::EWidget::Ptr *m_widget = {};
	};

}
