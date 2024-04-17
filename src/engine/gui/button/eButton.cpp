//◦ EggEngine ◦
#include "eButton.h"
#include "engine/debug/eAssert.h"
#include "engine/common/eRect.h"

using namespace Engine::GUI;


EButton::EButton()
{

}


EButton::~EButton()
{

}


void EButton::SetPosition(const FPoint &pos)
{
	m_position = pos;
	CalcCurrentSprite();
}


void EButton::SetScale(const FPoint &scale)
{
	m_scale = scale;
	CalcCurrentSprite();
}

void EButton::SetScale(const float scale)
{
	m_scale.x = scale;
	m_scale.y = scale;
	CalcCurrentSprite();
}


void EButton::SetSpriteNormal(const Engine::Assets::EAssetSprite::Ptr &sprite)
{
	m_spriteNormal = sprite;
	m_sprite = sprite;
	CalcCurrentSprite();
}


void EButton::SetSpritePushed(const Engine::Assets::EAssetSprite::Ptr &sprite)
{
	m_spritePushed = sprite;
}


void EButton::SetSpriteDisabled(const Engine::Assets::EAssetSprite::Ptr &sprite)
{
	m_spriteDisabled = sprite;
}


void EButton::CalcCurrentSprite()
{
	if (m_sprite) {
		m_source = m_sprite->SourceRect().SDL();
		const float width = m_source.w * m_scale.x + 1;
		const float height = m_source.h * m_scale.y + 1;
		m_screen.x = m_position.x - width / 2;
		m_screen.y = m_position.y - height / 2;
		m_screen.w = width;
		m_screen.h = height;
	}
}


void EButton::OnCapture()
{
	m_captured = true;
}

//  нажали на кнопку
void EButton::OnPushdown()
{
	m_pushed = true;
	m_sprite = m_spritePushed ? m_spritePushed : m_spriteNormal;
	CalcCurrentSprite();
}

void EButton::OnPushup()
{
	m_pushed = false;
	m_sprite = m_spriteNormal;
	CalcCurrentSprite();
}

void EButton::OnClick()
{
	if (click_signal) {
		std::invoke(click_signal);
	}
}

void EButton::OnRelease()
{
	m_captured = false;
}

bool EButton::Input(const Engine::Input::TControls &controls)
{
	if (!m_enabled) {
		return false;
	}
	
	if (controls.touch.pressed) {
		if (Engine::PointInRect(controls.touch.pos, m_screen)) {
			if (!m_captured) {
				OnCapture();
			}
			if (!m_pushed) {
				OnPushdown();
			}
		}
	}
	if (controls.touch.moving && m_captured) {
		if (Engine::PointInRect(controls.touch.pos, m_screen)) {
			if (!m_pushed) {
				OnPushdown();
			}
		} else {
			if (m_pushed) {
				OnPushup();
			}
		}
	}
	if (controls.touch.released) {
		if (m_pushed) {
			OnPushup();
		}
		if (m_captured) {
			if (Engine::PointInRect(controls.touch.pos, m_screen)) {
				OnClick();
			}
			OnRelease();
		}
	}
	
	return m_captured;
}
	

void EButton::Update(const double dt)
{
	
}


void EButton::Render(const Engine::Render::ESpriteBatch::UPtr& context)
{
	if (m_sprite) {
		const auto texture = m_sprite->MakeTexture(context);
		context->RenderCopyF(texture, &m_source, &m_screen);
	}
}


