//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <queue>

#include "ComponentPlayerControl.h"
#include "map/camera/Camera.h"

#include "engine/CoreSDL.h"
#include "engine/gui/eWidget.h"
#include "engine/assets/texture/eAssetSprite.h"
#include "engine/render/eSpriteBatch.h"
#include "engine/input/eControls.h"
#include "engine/common/eRect.h"

namespace Game::Components
{


	// GUI ситема для управления персонажем игрока
	class AWidgetPlayerControl : public Engine::GUI::EWidget
	{
	public:
		using Ptr		= std::shared_ptr<AWidgetPlayerControl>;
		using WeakPtr	= std::weak_ptr<AWidgetPlayerControl>;
		using UPtr		= std::unique_ptr<AWidgetPlayerControl>;

	public:
		AWidgetPlayerControl(const Map::ACamera::Ptr &camera, const AComponentPlayerControl::Ptr &control);
		virtual ~AWidgetPlayerControl();
		
	public:
		bool IsInputCaptured() const override final { return m_captured; }
		bool Input(const Engine::Input::TControls &controls) override final;
		void Update(const double dt) override final;
		void Render(const Engine::Render::ESpriteBatch::UPtr& context) final;

	public:
		void SetPointSprite(const Engine::Assets::EAssetSprite::Ptr &sprite);
		
	private:
		void OnCapture(const Engine::IPoint &pos); //  Захват управления кнопки
		void OnMoving(const Engine::IPoint &pos); //Движение мышкой
		void OnRelease();
		void OnClick();
		
		void OnPlayerMoving(const std::vector<Engine::IPoint> &points);

	private:
		const Map::ACamera::Ptr 			m_camera;
		const AComponentPlayerControl::Ptr 	m_control;
		
		Engine::Assets::EAssetSprite::Ptr	m_pointSprite; 	//Спрайт точка для обозначения пути движения персонажа
		std::vector<Engine::IPoint> 		m_points;		//Точки по которому пойдет персонаж
		
		bool m_captured	= {}; //  Захватили управление
		float m_clickTime = {}; // Время когда нажали на кнопку
		Engine::IRect m_clickArea = {}; //Область определения нажатия на кнопку
		Engine::IPoint m_touchScrolling = {}; //Начало скроллинга камеры
		Engine::FPoint m_cameraScrolling = {}; //Позиция камеры для скроллинга
		
		Engine::IPoint m_movingDirect = {}; //Куда движется персонаж
	};


}
