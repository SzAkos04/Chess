#pragma once

#include "debug.hpp"
#include <SDL2/SDL.h>
#include <utility>

enum class PieceColor { WHITE, BLACK };

enum class PieceType {
    PAWN,   // 1
    KNIGHT, // 3
    BISHOP, // 3
    ROOK,   // 5
    QUEEN,  // 9
    KING,   // 11

    UNKNOWN,
};

class piece_t {
  public:
    piece_t(PieceColor color, PieceType type, int col, int row);
    ~piece_t();

    void render(SDL_Renderer *renderer);

    bool validMove(int col, int row);

    PieceColor getColor() { return mColor; }
    PieceType getType() { return mType; }

    std::pair<int, int> getPos() { return mPos; }

    bool getMoved() { return mMoved; }
    void setMoved(bool to) { mMoved = to; }

    bool getSelected() { return mSelected; }
    void setSelected(bool to) { mSelected = to; }

  private:
    SDL_Rect mRect;

    PieceColor mColor;
    PieceType mType;

    // first is col, second is row
    std::pair<int, int> mPos;

    bool mMoved = false;
    bool mSelected = false;
};
