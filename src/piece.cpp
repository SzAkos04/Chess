#include "debug.hpp"
#include "piece.hpp"

#include <cmath>
#include <string>

#define TILE_SIZE 100

piece_t::piece_t(PieceColor color, PieceType type, int col, int row) {
    mRect = {
        col * TILE_SIZE + 5,
        row * TILE_SIZE + 5,
        TILE_SIZE - 10,
        TILE_SIZE - 10,
    };

    mColor = color;
    mType = type;

    mPos = std::pair(col, row);
}

piece_t::~piece_t() {}

void piece_t::render(SDL_Renderer *renderer) {
    std::string color_str = (mColor == PieceColor::WHITE) ? "white" : "black";
    std::string piece_str = (mType == PieceType::PAWN)     ? "pawn"
                            : (mType == PieceType::KNIGHT) ? "knight"
                            : (mType == PieceType::BISHOP) ? "bishop"
                            : (mType == PieceType::ROOK)   ? "rook"
                            : (mType == PieceType::QUEEN)  ? "queen"
                            : (mType == PieceType::KING)   ? "king"
                                                           : "";
    if (piece_str.empty()) {
        throw std::runtime_error("Unknown piece type");
    }
    SDL_Surface *image = SDL_LoadBMP(
        ("./assets/" + color_str + "_" + piece_str + ".bmp").c_str());
    if (!image) {
        throw std::runtime_error(
            std::string("Failed to create piece surface: ") + SDL_GetError());
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if (!texture) {
        throw std::runtime_error(
            std::string("Failed to create piece texture: ") + SDL_GetError());
    }

    SDL_RenderCopy(renderer, texture, nullptr, &mRect);

    SDL_DestroyTexture(texture);
}

bool piece_t::validMove(int col, int row) {
    switch (mType) {
    case PieceType::PAWN: {
        int direction = (mColor == PieceColor::WHITE) ? -1 : 1;
        if (col == mPos.first) {
            return (row == mPos.second + direction) ||
                   (!mMoved && row == mPos.second + 2 * direction);
        } else {
            return false;
        }
    }
    case PieceType::KNIGHT: {
        return (row == mPos.second - 2 && col == mPos.first - 1) ||
               (row == mPos.second - 2 && col == mPos.first + 1) ||
               (row == mPos.second - 1 && col == mPos.first - 2) ||
               (row == mPos.second - 1 && col == mPos.first + 2) ||
               (row == mPos.second + 1 && col == mPos.first - 2) ||
               (row == mPos.second + 1 && col == mPos.first + 2) ||
               (row == mPos.second + 2 && col == mPos.first - 1) ||
               (row == mPos.second + 2 && col == mPos.first + 1);
    }
    case PieceType::BISHOP: {
        return std::abs(row - mPos.second) == std::abs(col - mPos.first) &&
               row != mPos.second && col != mPos.first;
    }
    case PieceType::ROOK: {
        return (row == mPos.second) ^ (col == mPos.first);
    }
    case PieceType::QUEEN: {
        return (std::abs(row - mPos.second) == std::abs(col - mPos.first) &&
                row != mPos.second && col != mPos.first) ||
               (row == mPos.second) ^ (col == mPos.first);
    }
    case PieceType::KING: {
        return (row == mPos.second - 1 && col == mPos.first - 1) ||
               (row == mPos.second - 1 && col == mPos.first) ||
               (row == mPos.second - 1 && col == mPos.first + 1) ||
               (row == mPos.second && col == mPos.first - 1) ||
               (row == mPos.second && col == mPos.first + 1) ||
               (row == mPos.second + 1 && col == mPos.first - 1) ||
               (row == mPos.second + 1 && col == mPos.first) ||
               (row == mPos.second + 1 && col == mPos.first + 1);
    }
    default:
        throw std::runtime_error("Unknown piece type");
    }
}
