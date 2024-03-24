//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <SDL.h>
#include <SDL_assert.h>


#ifdef EN_ENABLE_ASSERT
#define sassert(exp)	SDL_assert(exp)
#define sassert2(exp, text) SDL_assert((exp) && (text))
#else
#define sassert(exp)	; // assert(exp)
#define sassert2(exp, text) ;
#endif



