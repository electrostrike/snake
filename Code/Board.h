#ifndef BOARD_H
#define BOARD_H

#include "Constant.h"
#include "Snake.h"
#include "Apple.h"

class Board {
    private:

    public:
        Board();
        void DrawBoard(SDL_Renderer* renderer, Snake snake, Apple apple);
};

#endif // BOARD_H
