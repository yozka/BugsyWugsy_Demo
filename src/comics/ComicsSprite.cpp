//◦ EggEngine ◦
#include "ComicsSprite.h"
#include "engine/common/eUtils.h"

using namespace Comics;


void AComicsSprite::Load(Engine::Xml::Node *root, const Engine::Assets::EAssetResources::Ptr &assets)
{
	m_sprite = assets->Find<Engine::Assets::EAssetSprite>(Engine::Xml::ToString(root, "name"));
	
	const auto source = m_sprite->SourceRect().SDL();
	
	m_dest.x = Engine::Xml::ToInteger(root, "x");
	m_dest.y = Engine::Xml::ToInteger(root, "y");
	m_dest.w = Engine::Xml::ToInteger(root, "width", source.w);
	m_dest.h = Engine::Xml::ToInteger(root, "height", source.h);
}

void AComicsSprite::Render(const Engine::Render::ESpriteBatch::UPtr& context)
{
	if (m_sprite) {
		const auto texture = m_sprite->MakeTexture(context);
		if (texture) {
			const auto source = m_sprite->SourceRect().SDL();
			context->RenderCopyF(texture, &source, &m_dest);
		}
	}
}
