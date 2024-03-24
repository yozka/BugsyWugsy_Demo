//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <SDL.h>

namespace Engine::Render
{
	struct TScreenInfo
	{
		bool IsNull() const { return screenWidth == 0 && screenHeigh == 0; }

		int screenWidth = {};
		int screenHeigh = {};
		float dpi = {};
		float scale = {};
	};


	// Контекст отрисовки на экране
	class ERenderContext
	{
	public:
		using UPtr		= std::unique_ptr<ERenderContext>;
		using Ptr		= std::shared_ptr<ERenderContext>;
		using WeakPtr	= std::weak_ptr<ERenderContext>;

	public:
		ERenderContext(SDL_Renderer* renderer);
		virtual ~ERenderContext();
		
	public:
#if EN_PLATFORM_EMSCRIPTEN
		void Init(const int width = 0, const int height = 0);
#else
		void Init();
#endif

		void Destroy();
		bool IsValid() const { return m_renderer != nullptr; }

	public:
		float DisplayDPI()	const { return m_displayDPI; }
		int DisplayWidth()	const { return m_displayWidth; }
		int DisplayHeight() const { return m_displayHeight; }
		int RenderWidth()	const { return m_renderWidth; }
		int RenderHeight()	const { return m_renderHeight; }

		TScreenInfo ScreenInfo() const;

	public:
		void RenderClear(const Uint8 red = 100, const Uint8 green = 149, const Uint8 blue = 237);
		void RenderPresent();
		//void RenderGeometry(SDL_Texture* texture, const SDL_Vertex *vertexts, const int count);
		//void RenderRect(const SDL_FRect &rect, const SDL_Color &color);
		void RenderCopy(SDL_Texture *texture, const SDL_Rect *source, const SDL_Rect *destination);
		
		void Flush();


	public:
		SDL_Texture* CreateTexture(SDL_Surface* surface);
		SDL_Texture* CreateTexturePow2HI(SDL_Surface* surface);
		
		
	private:
		SDL_Renderer* m_renderer	= { nullptr };
		int m_displayWidth			= { 0 };
		int m_displayHeight			= { 0 };
		int m_renderWidth			= { 0 };
		int m_renderHeight			= { 0 };
		float m_displayDPI			= { 0 };
	};


}
