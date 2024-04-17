//◦ EggEngine ◦
#include "ComicsSlide.h"
#include "engine/common/eUtils.h"
#include "ComicsText.h"
#include "ComicsSprite.h"

using namespace Comics;


void AComicsSlide::Load(Engine::Xml::Node *root, const Engine::Assets::EAssetResources::Ptr &assets)
{
	std::string colorName = Engine::Xml::ToString(root, "color");
	if (colorName.empty()) {
		m_drawColor = false;
	} else {
		m_drawColor = true;
		m_color = Engine::StringToColor(colorName, m_color);
	}

	m_loop = Engine::Xml::ToBool(root, "musicLoop", m_loop);
	m_fade = Engine::Xml::ToInteger(root, "musicFade", m_fade);
	std::string musicName = Engine::Xml::ToString(root, "music");
	if (!musicName.empty()) {
		m_music = assets->Find<Engine::Assets::EAssetMusic>(musicName);
	}
	
	std::string sampleName = Engine::Xml::ToString(root, "sample");
	if (!sampleName.empty()) {
		m_sample = assets->Find<Engine::Assets::EAssetSample>(sampleName);
	}
	
	auto node = root->FirstChild();
	while (node) {
		auto widget = node->ToElement();
		const std::string type = node->Value();
		if (type == "text") {
			LoadText(widget, assets);
		}
		if (type == "sprite") {
			LoadSprite(widget, assets);
		}
		node = node->NextSibling();
	}
	
}


void AComicsSlide::LoadText(Engine::Xml::Node *node, const Engine::Assets::EAssetResources::Ptr &assets)
{
	auto text = std::make_shared<AComicsText>();
	text->Load(node, assets);
	m_widgets.push_back(text);
}


void AComicsSlide::LoadSprite(Engine::Xml::Node *node, const Engine::Assets::EAssetResources::Ptr &assets)
{
	auto sprite = std::make_shared<AComicsSprite>();
	sprite->Load(node, assets);
	m_widgets.push_back(sprite);
}


void AComicsSlide::Render(const Engine::Render::ESpriteBatch::UPtr& context)
{
	if (m_drawColor) {
		SDL_FRect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = context->RenderWidth();
		rect.h = context->RenderHeight();
		context->RenderFillRect(rect, m_color);
	}
	
	for (auto& widget : m_widgets) {
		widget->Render(context);
	}
}


void AComicsSlide::Activate()
{
	if (m_music) {
		Mix_FadeOutMusic(m_fade);
		Mix_PlayMusic(m_music->GetMusic(), m_loop ? -1 : 0);
	}
	
	if (m_sample) {
		Mix_PlayChannel(-1, m_sample->GetSample(), 0);
	}
}
