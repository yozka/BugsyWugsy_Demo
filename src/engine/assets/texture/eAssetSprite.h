//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "engine/assets/eAsset.h"
#include "engine/common/eRect.h"
#include "engine/render/eGraphics.h"

namespace Engine::Assets
{

	class EAssetSprite : public EAsset
	{
	public:
		using Ptr = std::shared_ptr<EAssetSprite>;
		using UPtr = std::unique_ptr<EAssetSprite>;
		
	public:
		EAssetSprite() = default;
		~EAssetSprite() override = default;
	
	public:
		template <class T>
		SDL_Texture* MakeTexture(const std::unique_ptr<T> &context)
		{
			if (auto obj = context.get()) {
				return MakeTexture(*obj);
			}
			return {};
		}

	public:
		virtual SDL_Texture* MakeTexture(Engine::Render::EGraphics &context) = 0; //Создание подготовка текстуры
		virtual IRect SourceRect() const = 0; //Область спрайта в текстуре
		virtual IPoint SizeTexture() const = 0; //Размерность самой текстуры
		
	};

}
