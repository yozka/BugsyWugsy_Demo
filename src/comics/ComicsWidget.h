//◦ EggEngine ◦
#pragma once
#include <memory>

#include "engine/CoreSDL.h"
#include "engine/xml/eTinyxml.h"
#include "engine/assets/eAssetResources.h"
#include "engine/render/eSpriteBatch.h"

namespace Comics
{

	//Граф елемент
	class AComicsWidget
	{
	public:
		using UPtr		= std::unique_ptr<AComicsWidget>;
		using Ptr		= std::shared_ptr<AComicsWidget>;
		using WeakPtr	= std::weak_ptr<AComicsWidget>;

	public:
		virtual void Render(const Engine::Render::ESpriteBatch::UPtr& context) = 0;
		virtual void Load(Engine::Xml::Node *root, const Engine::Assets::EAssetResources::Ptr &assets) = 0;
	};

}
