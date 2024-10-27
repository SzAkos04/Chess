#pragma once

#include "piece.hpp"
#include "tile.hpp"

#include <SDL2/SDL.h>
#include <array>

class board_t {
  public:
    board_t();
    ~board_t();

    void handleEvents(SDL_Event e);
    void render(SDL_Renderer *renderer);

    std::array<tile_t, 64> getTiles() { return mTiles; }

  private:
    std::array<tile_t, 64> mTiles;

    PieceColor mRound = PieceColor::WHITE;

    void handleRightClick(int x, int y);
    void handleLeftClick(int x, int y);
};
