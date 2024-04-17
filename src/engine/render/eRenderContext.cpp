//◦ EggEngine ◦
#include "eRenderContext.h"


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
	
	SDL_RenderSetIntegerScale(m_renderer, SDL_TRUE);
	
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


void ERenderContext::RenderGeometry(SDL_Texture* texture, const SDL_Vertex *vertexts, const int count, const int *indices, int countIndices)
{
	if (m_renderer) {
		SDL_RenderGeometry(m_renderer, texture, vertexts, count, indices, countIndices);
	}
}


void ERenderContext::RenderRect(const SDL_FRect& rect, const SDL_Color& color)
{
	if (m_renderer) {
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRectF(m_renderer, &rect);
	}
}


void ERenderContext::RenderFillRect(const SDL_FRect& rect, const SDL_Color& color)
{
	if (m_renderer) {
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRectF(m_renderer, &rect);
	}
}


void ERenderContext::Flush()
{
	if (m_renderer) {
		SDL_RenderFlush(m_renderer);
	}
}


SDL_Texture* ERenderContext::CreateTexture(SDL_Surface* surface)
{
	if (m_renderer) {
		return SDL_CreateTextureFromSurface(m_renderer, surface);
	}
	return nullptr;
}


void ERenderContext::RenderCopy(SDL_Texture *texture, const SDL_Rect *source, const SDL_Rect *destination)
{
	if (m_renderer) {
		SDL_RenderCopy(m_renderer, texture, source, destination);
	}
}


void ERenderContext::RenderCopyF(SDL_Texture *texture, const SDL_Rect *source, const SDL_FRect *destination)
{
	if (m_renderer) {
		SDL_RenderCopyF(m_renderer, texture, source, destination);
	}
}
