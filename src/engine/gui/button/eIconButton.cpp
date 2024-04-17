//◦ EggEngine ◦
#include "eIconButton.h"
#include "engine/debug/eAssert.h"
#include "engine/common/eRect.h"

using namespace Engine::GUI;


EIconButton::EIconButton()
{

}


EIconButton::~EIconButton()
{

}


void EIconButton::SetIconOffset(const FPoint &offset)
{
	m_iconOffset = offset;
	CalcCurrentSprite();
}


void EIconButton::SetIconScale(const FPoint &scale)
{
	m_iconScale = scale;
	CalcCurrentSprite();
}

void EIconButton::SetIconScale(const float scale)
{
	m_iconScale.x = scale;
	m_iconScale.y = scale;
	CalcCurrentSprite();
}


void EIconButton::SetSpriteIconNormal(const Engine::Assets::EAssetSprite::Ptr &sprite)
{
	m_iconNormal = sprite;
	m_icon = sprite;
	CalcCurrentSprite();
}


void EIconButton::SetSpriteIconPushed(const Engine::Assets::EAssetSprite::Ptr &sprite)
{
	m_iconPushed = sprite;
}


void EIconButton::SetSpriteIconDisabled(const Engine::Assets::EAssetSprite::Ptr &sprite)
{
	m_iconDisabled = sprite;
}


void EIconButton::CalcCurrentSprite()
{
	Super::CalcCurrentSprite();
	if (m_icon) {
		const auto scale = Scale() * m_iconScale * m_iconPushedScale;
		const auto pos = Position() + m_iconOffset;
		
		m_iconSource = m_icon->SourceRect().SDL();
		const float width = m_iconSource.w * scale.x + 1;
		const float height = m_iconSource.h * scale.y + 1;
		m_iconScreen.x = pos.x - width / 2;
		m_iconScreen.y = pos.y - height / 2;
		m_iconScreen.w = width;
		m_iconScreen.h = height;
	}
}

//  нажали на кнопку
void EIconButton::OnPushdown()
{
	m_iconPushedScale = { 1.0f, 0.8f };
	Super::OnPushdown();
}

void EIconButton::OnPushup()
{
	m_iconPushedScale = { 1.0f, 1.0f };
	Super::OnPushup();
}

void EIconButton::Render(const Engine::Render::ESpriteBatch::UPtr& context)
{
	Super::Render(context);
	if (m_icon) {
		const auto texture = m_icon->MakeTexture(context);
		context->RenderCopyF(texture, &m_iconSource, &m_iconScreen);
	}
}


