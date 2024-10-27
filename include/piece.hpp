#pragma once

#include <SDL2/SDL.h>

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

  private:
    SDL_Rect mRect;

    PieceColor mColor;
    PieceType mType;
    int mCol, mRow;

    bool mHasMoved = false;
};
