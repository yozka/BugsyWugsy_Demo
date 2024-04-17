//◦ EggEngine ◦
#include "ComicsText.h"
#include "engine/common/eUtils.h"

using namespace Comics;


void AComicsText::Load(Engine::Xml::Node *root, const Engine::Assets::EAssetResources::Ptr &assets)
{
	m_label.SetFont(assets->Find<Engine::Assets::EAssetFont>(Engine::Xml::ToString(root, "font")));
	m_label.SetColor(Engine::StringToColor(Engine::Xml::ToString(root, "color"), {}));
	m_label.SetScale(Engine::Xml::ToFloat(root, "scale", 1.0f));
	
	Engine::FPoint pos;
	pos.x = Engine::Xml::ToInteger(root, "x");
	pos.y = Engine::Xml::ToInteger(root, "y");
	m_label.SetPosition(pos);

	
	std::string text = root->GetText();
	m_label.SetText(text);
}

void AComicsText::Render(const Engine::Render::ESpriteBatch::UPtr& context)
{
	m_label.Render(context);
}
