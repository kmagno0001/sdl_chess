#pragma once

#include <SDL2/SDL.h>

enum Type_piece { PAWN, TOWER, BISHOP, KNIGHT, KING, QUEEN, NONE };

struct Piece {
    int x {0};
    int y {0};
    SDL_Texture* texture;
    Type_piece ty_piece;
};