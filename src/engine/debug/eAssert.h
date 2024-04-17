//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "engine/CoreSDL.h"


#ifdef EN_ENABLE_ASSERT
#define sassert(exp) SDL_assert(exp)
#define sassert2(exp, text) SDL_assert((exp) && (text))
#else
#define sassert(exp) exp // assert(exp)
#define sassert2(exp, text) exp
#endif



