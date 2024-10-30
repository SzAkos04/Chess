#include "board.hpp"
#include "debug.hpp"
#include "tile.hpp"

board_t::board_t() {
    for (int i = 0; i < 8 * 8; ++i) {
        mTiles.at(i) = tile_t(i % 8, i / 8);
    }
}

board_t::~board_t() {}

void board_t::handleEvents(SDL_Event e) {
    switch (e.type) {
    case SDL_MOUSEBUTTONDOWN:
        switch (e.button.button) {
        case SDL_BUTTON_RIGHT:
            handleRightClick(e.button.x, e.button.y);
            break;
        case SDL_BUTTON_LEFT:
            handleLeftClick(e.button.x, e.button.y);
            break;
        }
    }
}

void board_t::render(SDL_Renderer *renderer) {
    for (auto &tile : mTiles) {
        tile.render(renderer);
    }
}

void board_t::handleRightClick(int x, int y) {
    tile_t *clicked = &mTiles.at((y / TILE_SIZE) * 8 + (x / TILE_SIZE));

    clicked->setHighlighted(!clicked->isHighlighted());
}

void board_t::handleLeftClick(int x, int y) {
    tile_t *clicked = &mTiles.at((y / TILE_SIZE) * 8 + (x / TILE_SIZE));

    clearHighlights();
    clearSelections();

    if (clicked->getPiece().has_value()) {
        piece_t &piece = clicked->getPiece()->get();
        if (piece.getColor() == mRound) {
            debug("Ready to move!");
            piece.setSelected(true);

            for (auto &tile : mTiles) {
                if (piece.validMove(tile.getPos().first,
                                    tile.getPos().second)) {
                    tile.setHighlighted(true);
                }
            }
        } else {
            debug("Other color's turn!");
        }
    } else {
        debug("Clicked on empty tile");
    }

    for (auto &tile : mTiles) {
        if (tile.getPiece().has_value()) {
            piece_t &piece = tile.getPiece()->get();
            if (piece.getSelected()) {
                debug("Tile (" + std::string(1, piece.getPos().first + 'A') +
                      ":" + std::to_string(piece.getPos().second + 1) +
                      ") selected");
            }
        }
    }
}

void board_t::clearHighlights() {
    for (auto &tile : mTiles) {
        tile.setHighlighted(false);
    }
}

void board_t::clearSelections() {
    for (auto &tile : mTiles) {
        if (tile.getPiece().has_value()) {
            piece_t &piece = tile.getPiece()->get();
            piece.setSelected(false);
        }
    }
}
