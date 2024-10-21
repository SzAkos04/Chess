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

  private:
    SDL_Rect mRect;
    SDL_Surface *image = nullptr;

    PieceColor mColor;
    PieceType mType;
    int mCol, mRow;
};
