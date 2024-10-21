#include "state.hpp"

#include <stdexcept>
#include <string>

state_t::state_t() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("Failed to initialize SDL2: ") +
                                 SDL_GetError());
    }

    mWindow = SDL_CreateWindow("CHESS", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    if (!mWindow) {
        throw std::runtime_error(std::string("Failed to create window: ") +
                                 SDL_GetError());
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!mRenderer) {
        throw std::runtime_error(std::string("Failed to create renderer: ") +
                                 SDL_GetError());
    }
}

state_t::~state_t() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void state_t::run() {
    mRunning = true;
    while (mRunning) {
        handleEvents();
        render();
    }
}

void state_t::handleEvents() {
    SDL_Event e;
    // would be better but for some reason it lags
    /* SDL_WaitEvent(&e); */

    while (SDL_PollEvent(&e)) {

        mBoard.handleEvents(e);

        switch (e.type) {
        case SDL_QUIT:
            mRunning = false;
            break;
        }
    }
}

void state_t::render() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    mBoard.render(mRenderer);

    SDL_RenderPresent(mRenderer);
}
