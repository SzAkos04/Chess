#pragma once

#include "board.hpp"
#include <SDL2/SDL.h>

class state_t {
  public:
    state_t();
    ~state_t();

    void run();

  private:
    bool mRunning = false;
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    board_t mBoard;

    void handleEvents();
    void render();
};
