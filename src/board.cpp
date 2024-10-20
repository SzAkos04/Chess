#include "board.hpp"

board_t::board_t() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            mTiles[row * 8 + col] = tile_t(col, row);
        }
    }
}

board_t::~board_t() {}

void board_t::handleEvents(SDL_Event e) {
    switch (e.type) {
    case SDL_MOUSEBUTTONDOWN:
        switch (e.button.button) {
        case SDL_BUTTON_RIGHT:
            mTiles.at((e.button.y / TILE_SIZE) * 8 + (e.button.x / TILE_SIZE))
                .handleRightClick();
        }
    }
}

void board_t::render(SDL_Renderer *renderer) {
    for (auto &tile : mTiles) {
        tile.render(renderer);
    }
}
