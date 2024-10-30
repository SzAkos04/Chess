#pragma once

#include "debug.hpp"
#include "piece.hpp"

#include <SDL2/SDL.h>
#include <optional>
#include <utility>

#define TILE_SIZE 100

enum class TileColor {
    WHITE,
    BLACK,
};

class tile_t {
  public:
    tile_t() = default;
    tile_t(int col, int row);
    ~tile_t();

    void render(SDL_Renderer *renderer);

    std::pair<int, int> getPos() { return mPos; }

    bool isHighlighted() { return mHighlighted; }
    void setHighlighted(bool to) { mHighlighted = to; };

    // idk what this is but it works
    std::optional<std::reference_wrapper<piece_t>> getPiece() {
        return mPiece ? std::optional<std::reference_wrapper<piece_t>>(*mPiece)
                      : std::nullopt;
    }
    void setPiece(std::optional<piece_t> to) { mPiece = to; }

  private:
    SDL_Rect mRect;
    TileColor mColor;

    // first is col, second is row
    std::pair<int, int> mPos;

    bool mHighlighted = false;

    std::optional<piece_t> mPiece = std::nullopt;
};
