#include "debug.hpp"
#include "piece.hpp"
#include "tile.hpp"

#include <cctype>
#include <string>

const char board[8][8] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
};

tile_t::tile_t(int col, int row) {
    mRect = {
        col * TILE_SIZE,
        row * TILE_SIZE,
        TILE_SIZE,
        TILE_SIZE,
    };
    mColor = (col + row) % 2 == 0 ? TileColor::WHITE : TileColor::BLACK;
    mPos = std::pair(col, row);

    if (board[row][col] == ' ') {
        // TODO: make this more future-proof
        return;
    }
    PieceColor color =
        (std::isupper(board[row][col])) ? PieceColor::WHITE : PieceColor::BLACK;

    char ch = std::tolower(board[row][col]);
    PieceType type = PieceType::UNKNOWN;
    switch (ch) {
    case 'p':
        type = PieceType::PAWN;
        break;
    case 'n':
        type = PieceType::KNIGHT;
        break;
    case 'b':
        type = PieceType::BISHOP;
        break;
    case 'r':
        type = PieceType::ROOK;
        break;
    case 'q':
        type = PieceType::QUEEN;
        break;
    case 'k':
        type = PieceType::KING;
        break;
    default:
        break;
    }

    mPiece.emplace(color, type, mPos.first, mPos.second);
}

tile_t::~tile_t() {}

void tile_t::render(SDL_Renderer *renderer) {
    if (mHighlighted) {
        if (mColor == TileColor::WHITE) {
            SDL_SetRenderDrawColor(renderer, 137, 196, 244, 255);
        } else if (mColor == TileColor::BLACK) {
            SDL_SetRenderDrawColor(renderer, 112, 169, 215, 255);
        }
    } else {
        if (mColor == TileColor::WHITE) {
            SDL_SetRenderDrawColor(renderer, 234, 221, 202, 255);
        } else if (mColor == TileColor::BLACK) {
            SDL_SetRenderDrawColor(renderer, 111, 78, 55, 255);
        }
    }

#if DEBUG
    if (mPiece->getSelected() == true) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    }
#endif

    SDL_RenderFillRect(renderer, &mRect);

    if (mPiece.has_value()) {
        mPiece->render(renderer);
    }
}
