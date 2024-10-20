#include "tile.hpp"

#include "debug.hpp"
#include <string>

tile_t::tile_t(int col, int row) {
    mRect = {
        col * TILE_SIZE,
        row * TILE_SIZE,
        TILE_SIZE,
        TILE_SIZE,
    };
    mColor = (col + row) % 2 == 0 ? TileColor::WHITE : TileColor::BLACK;
    mCol = col, mRow = row;
}

tile_t::~tile_t() {}

void tile_t::render(SDL_Renderer *renderer) {
    if (mHighlighted) {
        if (mColor == TileColor::WHITE) {
            SDL_SetRenderDrawColor(renderer, 76, 201, 254, 255);
        } else if (mColor == TileColor::BLACK) {
            SDL_SetRenderDrawColor(renderer, 55, 175, 225, 255);
        }
    } else {
        if (mColor == TileColor::WHITE) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        } else if (mColor == TileColor::BLACK) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
    }

    SDL_RenderFillRect(renderer, &mRect);
}

void tile_t::handleRightClick() {
    mHighlighted = !mHighlighted;
    debug("Highlighted tile at " + std::to_string(mCol) + ":" +
          std::to_string(mRow));
}
