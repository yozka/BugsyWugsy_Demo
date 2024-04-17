//◦ EggEngine ◦
#pragma once
#include <memory>
#include "engine/CoreSDL.h"

namespace Engine::Render
{
	// Графический контекст
	class EGraphics
	{
	public:
		virtual ~EGraphics() = default;
		virtual SDL_Texture* CreateTexture(SDL_Surface* surface) = 0;
		
	};


}
