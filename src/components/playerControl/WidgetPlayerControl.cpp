//◦ EggEngine ◦
#include "WidgetPlayerControl.h"
#include "engine/debug/eAssert.h"
#include "engine/common/eRect.h"

using namespace Game::Components;


AWidgetPlayerControl::AWidgetPlayerControl(const Map::ACamera::Ptr &camera, const AComponentPlayerControl::Ptr &control)
	:
		m_camera(camera),
		m_control(control)
{

}


AWidgetPlayerControl::~AWidgetPlayerControl()
{

}


void AWidgetPlayerControl::OnCapture(const Engine::IPoint &pos)
{
	m_captured = true;

	//Данные для скроллинга карты
	m_touchScrolling = pos;
	m_cameraScrolling = m_camera->GetPosition();

	//Данные для обработки клика
	m_clickTime = 0.5f; //Время фиксации клика
	const int sizeArea = 10; //Область действия клика
	m_clickArea = {pos.x - sizeArea, pos.y - sizeArea, pos.x + sizeArea, pos.y + sizeArea};
	
}


void AWidgetPlayerControl::OnMoving(const Engine::IPoint &pos)
{
	Engine::IPoint direct = pos - m_touchScrolling;
	Engine::FPoint pt = m_cameraScrolling - m_camera->ScreenToWorld(direct);
	m_camera->SetPosition(pt);
}


void AWidgetPlayerControl::OnRelease()
{
	m_captured = false;
}


void AWidgetPlayerControl::OnClick()
{
	m_points.clear();
	const Engine::IPoint cell = m_camera->ScreenToWorldGrid(m_touchScrolling);
	m_control->MovingToGrid(cell, std::bind(&AWidgetPlayerControl::OnPlayerMoving, this, std::placeholders::_1));
}


bool AWidgetPlayerControl::Input(const Engine::Input::TControls &controls)
{
	const auto direct = m_movingDirect;
	if (controls.left.pressed) 		m_movingDirect.x =-1;
	if (controls.left.released) 	m_movingDirect.x = 0;
	if (controls.right.pressed) 	m_movingDirect.x = 1;
	if (controls.right.released)	m_movingDirect.x = 0;
	if (controls.up.pressed)		m_movingDirect.y =-1;
	if (controls.up.released)		m_movingDirect.y = 0;
	if (controls.down.pressed)		m_movingDirect.y = 1;
	if (controls.down.released)		m_movingDirect.y = 0;
	if (direct != m_movingDirect) {
		m_control->MovingToDirect(m_movingDirect);
	}
	
	if (controls.touch.pressed) {
		if (!m_captured) {
			OnCapture(controls.touch.pos);
		}
	}
	if (controls.touch.moving && m_captured) {
		OnMoving(controls.touch.pos);
	}
	if (controls.touch.released) {
		if (m_captured) {
			if (Engine::PointInRect(controls.touch.pos, m_clickArea) && m_clickTime > 0) {
				OnClick();
			}
			OnRelease();
		}
	}
	return m_captured;
}


void AWidgetPlayerControl::Update(const double dt)
{
	if (m_captured) {
		if (m_clickTime > 0) {
			m_clickTime -= dt;
		}
	}
}


void AWidgetPlayerControl::Render(const Engine::Render::ESpriteBatch::UPtr& context)
{
	if (m_pointSprite) {
		SDL_Texture* texture = {};
		SDL_Rect source;
		for (const auto point : m_points) {
			if (!texture) {
				texture = m_pointSprite->MakeTexture(context);
				source = m_pointSprite->SourceRect().SDL();
			}
			//
			Engine::IRect pt = m_camera->WorldGridToScreenRect(point);
			SDL_FRect dest;
			dest.x = pt.x1;
			dest.y = pt.y1;
			dest.w = pt.Width();
			dest.h = pt.Height();
			
			context->RenderCopyF(texture, &source, &dest);
		}
	}
}


void AWidgetPlayerControl::SetPointSprite(const Engine::Assets::EAssetSprite::Ptr &sprite)
{
	m_pointSprite = sprite;
}

void AWidgetPlayerControl::OnPlayerMoving(const std::vector<Engine::IPoint> &points)
{
	m_points.clear();
	m_points.insert(m_points.end(), points.begin(), points.end());
}
