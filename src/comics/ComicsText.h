//◦ EggEngine ◦
#pragma once
#include <memory>

#include "ComicsWidget.h"
#include "engine/CoreSDL.h"
#include "engine/gui/label/eLabel.h"

namespace Comics
{

	//Текстовый элемент
	class AComicsText : public AComicsWidget
	{
	public:
		using Super 	= AComicsWidget;
		using UPtr		= std::unique_ptr<AComicsText>;
		using Ptr		= std::shared_ptr<AComicsText>;
		using WeakPtr	= std::weak_ptr<AComicsText>;

	public:
		void Load(Engine::Xml::Node *root, const Engine::Assets::EAssetResources::Ptr &assets) override;
		void Render(const Engine::Render::ESpriteBatch::UPtr& context) override;
		
	private:
		Engine::GUI::ELabel m_label;
		
	};

}
