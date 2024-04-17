//◦ EggEngine ◦
#pragma once

#if defined(EN_PLATFORM_EMSCRIPTEN)

	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_mixer.h>
	#include <SDL2/SDL_assert.h>

#elif defined(EN_PLATFORM_MAC) || defined(EN_PLATFORM_WIN)
	
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_ttf.h>
	#include <SDL_mixer.h>
	#include <SDL_assert.h>

#else
	#error "OS missing SDL2 header file includes"
#endif
