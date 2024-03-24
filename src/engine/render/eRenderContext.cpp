//◦ EggEngine ◦
#include "eRenderContext.h"
#include "SDL_render.h"

using namespace Engine::Render;



ERenderContext::ERenderContext(SDL_Renderer* renderer)
	:
	m_renderer(renderer)
{
	Init();
}


ERenderContext::~ERenderContext()
{
	Destroy();
}


#if EN_PLATFORM_EMSCRIPTEN
void ERenderContext::Init(const int width, const int height)
#else
void ERenderContext::Init()
#endif
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	 
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	m_displayWidth = DM.w;
	m_displayHeight = DM.h;

#if EN_PLATFORM_EMSCRIPTEN
	m_renderWidth = width;
	m_renderHeight = height;
#else
	SDL_GetRendererOutputSize(m_renderer, &m_renderWidth, &m_renderHeight);
	if (auto window = SDL_RenderGetWindow(m_renderer)) {
		const int displayIndex = SDL_GetWindowDisplayIndex(window);
		SDL_GetDisplayDPI(displayIndex, &m_displayDPI, nullptr, nullptr);
	}
#endif
}


void ERenderContext::Destroy()
{
	if (m_renderer) {
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}


TScreenInfo ERenderContext::ScreenInfo() const
{
	TScreenInfo info;
	info.screenWidth = m_renderWidth;
	info.screenHeigh = m_renderHeight;
	info.dpi = m_displayDPI;

	return info;
}


void ERenderContext::RenderClear(const Uint8 red, const Uint8 green, const Uint8 blue)
{
	if (m_renderer) {
		SDL_SetRenderDrawColor(m_renderer, red, green, blue, 0xFF);
		SDL_RenderClear(m_renderer);
	}
}


void ERenderContext::RenderPresent()
{
	if (m_renderer) {
		SDL_RenderPresent(m_renderer);
	}
}

/*
void ERenderContext::RenderGeometry(SDL_Texture* texture, const SDL_Vertex *vertexts, const int count)
{
	if (m_renderer) {
		SDL_RenderGeometry(m_renderer, texture, vertexts, count, nullptr, 0);
	}
}
*/

/*
void ERenderContext::RenderRect(const SDL_FRect& rect, const SDL_Color& color)
{
	if (m_renderer) {
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRectF(m_renderer, &rect);
	}
}*/


void ERenderContext::Flush()
{
	if (m_renderer) {
	//	SDL_RenderFlush(m_renderer);
	}
}


SDL_Texture* ERenderContext::CreateTexture(SDL_Surface* surface)
{
	if (m_renderer) {
		return SDL_CreateTextureFromSurface(m_renderer, surface);
	}
	return nullptr;
}


int GetPow2HI(int value)
{
	for (int i = 1; i < 16; i++)
		if ((1 << i) >= value) return (1 << i);
	return 1 << 16; //!
}


SDL_Texture* ERenderContext::CreateTexturePow2HI(SDL_Surface* surface)
{
	if (!m_renderer) return nullptr;
	if (!surface) return nullptr;

	int w = GetPow2HI(surface->w);
	int h = GetPow2HI(surface->h);
	if (w < 8) w = 8; // safe
	if (h < 8) h = 8; // safe

	auto texture = SDL_CreateTexture(m_renderer, surface->format->format, SDL_TEXTUREACCESS_STREAMING, w, h);
	if (!texture) {
		return nullptr;
	}
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = surface->w;
	rect.h = surface->h;

	if (SDL_MUSTLOCK(surface)) {
		SDL_LockSurface(surface);
		SDL_UpdateTexture(texture, &rect, surface->pixels, surface->pitch);
		SDL_UnlockSurface(surface);
	}
	else {
		SDL_UpdateTexture(texture, &rect, surface->pixels, surface->pitch);
	}

	return texture;
}



void ERenderContext::RenderCopy(SDL_Texture *texture, const SDL_Rect *source, const SDL_Rect *destination)
{
	if (m_renderer) {
		SDL_RenderCopy(m_renderer, texture, source, destination);
	}
}

/*


		  // Declare rect of square
			SDL_Rect squareRect;

			// Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
			squareRect.w = std::min<int>(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
			squareRect.h = std::min<int>(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;

			// Square position: In the middle of the screen
			squareRect.x = SCREEN_WIDTH / 2 - squareRect.w / 2;
			squareRect.y = SCREEN_HEIGHT / 2 - squareRect.h / 2;


			// Event loop exit flag
			bool quit = false;

			// Event loop
			while (!quit)
			{
				SDL_Event e;

				// Wait indefinitely for the next available event
				SDL_WaitEvent(&e);

				// User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				// Initialize renderer color white for the background
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Clear screen
				SDL_RenderClear(renderer);

				// Set renderer color red to draw the square
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

				// Draw filled square
				SDL_RenderFillRect(renderer, &squareRect);

				// Update screen
				SDL_RenderPresent(renderer);
			}

*/
