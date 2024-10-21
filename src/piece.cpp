#include "debug.hpp"
#include "piece.hpp"
#include <SDL2/SDL_render.h>
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
    mCol = col;
    mRow = row;
}

piece_t::~piece_t() {}

void piece_t::render(SDL_Renderer *renderer) {
    switch (mColor) {
    case PieceColor::WHITE: {
        switch (mType) {
        case PieceType::PAWN: {
            image = SDL_LoadBMP("./assets/white_pawn.bmp");
            break;
        }
        case PieceType::KNIGHT: {
            image = SDL_LoadBMP("./assets/white_knight.bmp");
            break;
        }
        case PieceType::BISHOP: {
            image = SDL_LoadBMP("./assets/white_bishop.bmp");
            break;
        }
        case PieceType::ROOK: {
            image = SDL_LoadBMP("./assets/white_rook.bmp");
            break;
        }
        case PieceType::QUEEN: {
            image = SDL_LoadBMP("./assets/white_queen.bmp");
            break;
        }
        case PieceType::KING: {
            image = SDL_LoadBMP("./assets/white_king.bmp");
            break;
        }
        default:
            throw std::runtime_error("Unknown piece type");
        }
        break;
    }
    case PieceColor::BLACK: {
        switch (mType) {
        case PieceType::PAWN: {
            image = SDL_LoadBMP("./assets/black_pawn.bmp");
            break;
        }
        case PieceType::KNIGHT: {
            image = SDL_LoadBMP("./assets/black_knight.bmp");
            break;
        }
        case PieceType::BISHOP: {
            image = SDL_LoadBMP("./assets/black_bishop.bmp");
            break;
        }
        case PieceType::ROOK: {
            image = SDL_LoadBMP("./assets/black_rook.bmp");
            break;
        }
        case PieceType::QUEEN: {
            image = SDL_LoadBMP("./assets/black_queen.bmp");
            break;
        }
        case PieceType::KING: {
            image = SDL_LoadBMP("./assets/black_king.bmp");
            break;
        }
        default:
            throw std::runtime_error("Unknown piece type");
        }
        break;
    }
    }
    if (!image) {
        throw std::runtime_error(
            std::string("Failed to create piece surface: ") + SDL_GetError());
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    if (!texture) {
        throw std::runtime_error(
            std::string("Failed to create piece texture: ") + SDL_GetError());
    }

    SDL_RenderCopy(renderer, texture, nullptr, &mRect);

    SDL_DestroyTexture(texture);
}
