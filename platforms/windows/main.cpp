//◦ EggEngine ◦
#define SDL_MAIN_HANDLED // insert this
#include <iostream>
#include <SDL.h>
#include <Windows.h>
#include <algorithm>
#include <memory>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>



#include <ApplicationLogic.h>
#include <engine/debug/eAssert.h>
#include <engine/render/eRenderContext.h>





constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;



int SDL_main(int argc, char* argv[])
{
    auto app = std::make_unique<Game::AApplicationLogic>();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sassert2(false, "SDL Init error");
        return 0;
    }
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);
    TTF_Init();
    
    // Initialize SDL_mixer with our audio format
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        sassert2(false, "Error initializing SDL_mixer");
        return 0;
    }


    // Create window
    SDL_Window* window = SDL_CreateWindow("EggEngine", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window) {
        sassert2(false, "SDL Window could not be created");
        SDL_Quit();
        return 0;
    }

    // Create renderer
    auto context = std::make_unique<Engine::Render::ERenderContext>(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    if (context->IsValid()) {
        app->Init();


        auto ticks = SDL_GetTicks();
        bool quit = false;
        SDL_Event e;
        while (!quit) {

            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT || e.type == SDL_WINDOWEVENT_CLOSE) {
                    quit = true;
                }
                app->EventInput(e);
            }

            auto time = SDL_GetTicks();
            auto delta = time - ticks;
            ticks = time;
            app->Update(delta / 1000.0f);

            context->RenderClear();
            app->Render(context);
            context->RenderPresent();

            constexpr int timeFPS = 60;
            constexpr int delayFPS = 1000 / timeFPS;
            const int delay = delayFPS - delta;
            if (delay > 0) {
                SDL_Delay(delay);
            }
        }
        app->Done();
    }

    context->Destroy();
    SDL_DestroyWindow(window);
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}