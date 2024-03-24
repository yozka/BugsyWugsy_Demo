//◦ EggEngine ◦
#define SDL_MAIN_HANDLED // insert this
#include <iostream>
#include <algorithm>
#include <memory>
#include <utility>

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <assert.h>

#include <emscripten.h>
#include <emscripten/html5.h>

#include <ApplicationLogic.h>
#include <engine/render/eRenderContext.h>


constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

struct Unity
{
	using Ptr = Unity*;
	bool init = { false };
	Uint32 ticks = {};
	SDL_Window* window = {};
	Game::AApplicationLogic::UPtr app;
	Engine::Render::ERenderContext::UPtr context;
};


void MainLoop(Unity::Ptr unity)
{
	if (!unity) {
		emscripten_cancel_main_loop();
    	return;
	}

	if (!unity->init) {
		assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) == 0);
		assert(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG);
		//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		SDL_Renderer * renderer = {};
 		assert(SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE, &unity->window, &renderer) == 0);
		// Create window
		/*
		unity->window = SDL_CreateWindow("BugsyWugsy",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);*/
		assert(unity->window);

		unity->init = true;
		unity->ticks = SDL_GetTicks();
		unity->app = std::make_unique<Game::AApplicationLogic>();
		unity->context = std::make_unique<Engine::Render::ERenderContext>(renderer);
		//unity->context = std::make_unique<Engine::Render::ERenderContext>(SDL_CreateRenderer(unity->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

		assert(unity->context->IsValid());
		if (unity->context->IsValid()) {
			assert(unity->app->Init());
		}
		SDL_LogInfo(0, "Init completed");
		return;
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT || e.type == SDL_WINDOWEVENT_CLOSE) {
			unity->app->Done();
			unity->context->Destroy();
			SDL_DestroyWindow(unity->window);
			Mix_Quit();
			IMG_Quit();
			SDL_Quit();
    	    delete unity;
	        emscripten_cancel_main_loop();
			return;
		}
		if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
            unity->context->Init(e.window.data1, e.window.data2);
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Resized Display: %d, %d Render: %d, %d", unity->context->DisplayWidth(), unity->context->DisplayHeight(), unity->context->RenderWidth(), unity->context->RenderHeight());
        }

		unity->app->EventInput(e);
	}
	
	auto time = SDL_GetTicks();
	auto delta = time - unity->ticks;
	unity->ticks = time;
	unity->app->Update(delta / 1000.0f);
	
	unity->context->RenderClear();
	unity->app->Render(unity->context);
	unity->context->RenderPresent();

	//emscripten_set_main_loop_timing(EM_TIMING_RAF, 1);
}


int main(int argc, char **argv)
{
	auto unity = new Unity();
	//emscripten_set_main_loop(MainLoop, 0, 1);
	emscripten_set_main_loop_arg((em_arg_callback_func)MainLoop, unity, 0, true);
	//emscripten_set_main_loop_timing(EM_TIMING_RAF, 1);
	return 0;
}

