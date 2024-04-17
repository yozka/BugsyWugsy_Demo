//◦ EggEngine ◦
#define SDL_MAIN_HANDLED // insert this
#include <iostream>
#include <algorithm>
#include <memory>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_assert.h>
#include <assert.h>

#include <emscripten.h>
#include <emscripten/html5.h>

#include <ApplicationLogic.h>
#include <engine/render/eRenderContext.h>


class SystemUnity
{
	public:
		using Ptr = SystemUnity*;

	public:
		static void Loop(SystemUnity::Ptr unity);

	private:
		void Destroy();
		void Init();
		void PollEvent();
		void Update();
		void Render();

	private:
		bool 									m_init 		= { false };
		bool									m_closed	= { false };
		Uint32 									m_ticks 	= {};
		SDL_Window* 							m_window 	= {};
		Game::AApplicationLogic::UPtr 			m_app;
		Engine::Render::ERenderContext::UPtr	m_context;
};


//---------------------------------------------------------------------
void SystemUnity::Loop(SystemUnity::Ptr unity)
{
	if (!unity) {
		emscripten_cancel_main_loop();
    	return;
	}
	if (!unity->m_init) {
		unity->Init();
		return;
	}
	unity->PollEvent();
	if (unity->m_closed) {
		unity->Destroy();
		delete unity;
		emscripten_cancel_main_loop();
		return;
	}
	unity->Update();
	unity->Render();
}

void SystemUnity::Destroy()
{
	if (m_app) {
		m_app->Done();
		m_app = {};
	}
	if (m_context) {
		m_context->Destroy();
		m_context = {};
	}
	if (m_window) {
		SDL_DestroyWindow(m_window);
		m_window = {};
	}
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SystemUnity::Init()
{
	m_init = true;
	m_closed = false;
	assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) == 0);
	assert(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG);
	TTF_Init();
	
    int const frequency = EM_ASM_INT_V({
        var context;
        try {
            context = new AudioContext();
        } catch (e) {
            context = new webkitAudioContext();
        }
        return context.sampleRate;
    });
	assert(Mix_OpenAudioDevice(frequency, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096, nullptr, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE) == 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_Renderer * renderer = {};
 	assert(SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE, &m_window, &renderer) == 0);
	assert(m_window);
	assert(renderer);
	m_context = std::make_unique<Engine::Render::ERenderContext>(renderer);
	m_app = std::make_unique<Game::AApplicationLogic>();

	assert(m_context->IsValid());
	if (m_context->IsValid()) {
		assert(m_app->Init());
	}
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Init completed");
	m_ticks = SDL_GetTicks();
}

void SystemUnity::PollEvent()
{
	assert(m_context);
	assert(m_app);
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT || e.type == SDL_WINDOWEVENT_CLOSE) {
			m_closed = true;
		}
		if (e.window.event == SDL_WINDOWEVENT_RESIZED && m_context) {
            m_context->Init(e.window.data1, e.window.data2);
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Resized Display: %d, %d Render: %d, %d", m_context->DisplayWidth(), m_context->DisplayHeight(), m_context->RenderWidth(), m_context->RenderHeight());
        }
		if (m_app) {
			m_app->EventInput(e);
		}
	}
}

void SystemUnity::Update()
{
	assert(m_app);
	auto time = SDL_GetTicks();
	auto delta = time - m_ticks;
	m_ticks = time;
	m_app->Update(delta / 1000.0f);
}

void SystemUnity::Render()
{
	assert(m_context);
	assert(m_app);
	m_context->RenderClear();
	m_app->Render(m_context);
	m_context->RenderPresent();
}


//---------------------------------------------------------------------
int main(int argc, char **argv)
{
	auto unity = new SystemUnity();
	emscripten_set_main_loop_arg((em_arg_callback_func)SystemUnity::Loop, unity, 0, true);
	return 0;
}

