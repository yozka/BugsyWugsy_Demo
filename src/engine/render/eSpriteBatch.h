//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>
#include "eGraphics.h"
#include "eRenderContext.h"
#include "engine/CoreSDL.h"


namespace Engine::Render
{


	// Батчинг спрайтов
	class ESpriteBatch : public EGraphics
	{
	public:
		using UPtr		= std::unique_ptr<ESpriteBatch>;
		using Ptr		= std::shared_ptr<ESpriteBatch>;
		using WeakPtr	= std::weak_ptr<ESpriteBatch>;
		
	public:
		ESpriteBatch();
		virtual ~ESpriteBatch();
		
	public:
		void Begin(const ERenderContext::UPtr &context);
		void Flush();
		void End();
		
	public:
		int RenderWidth() const;
		int RenderHeight() const;
		
		void RenderFillRect(const SDL_FRect &rect, const SDL_Color &color);
		
		void RenderCopyF(SDL_Texture *texture, const SDL_Rect *source, const SDL_FRect *destination);
		void RenderGeometry(SDL_Texture* texture, const SDL_Vertex *vertexts, const int count, const int *indices, int countIndices);
		
	public:
		SDL_Texture* CreateTexture(SDL_Surface* surface) override final;
		
	private:
		ERenderContext* m_context = {};
		SDL_Texture* m_texture = {}; //Текущая текстура для батчинга
		int m_width = {};
		int m_height = {};
		std::vector<SDL_Vertex> m_vx;
		std::vector<int> m_indices;
		
	};


}
