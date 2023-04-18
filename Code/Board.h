#ifndef BOARD_H
#define BOARD_H

#include "Constant.h"
#include "Snake.h"
#include "Apple.h"
#include "Texture.h"

class Board {
    private:

    public:
        Board();
        void DrawBoard(SDL_Renderer* renderer, Snake& snake, Apple& apple);
        void DrawGameOver(SDL_Renderer* renderer, Snake& snake);
        void DrawUI(SDL_Renderer* renderer, TTF_Font* font, int score, int highScore);
        void DrawPressR(SDL_Renderer* renderer, TTF_Font* font);
        void FillBlack(SDL_Renderer* renderer);
};

#endif // BOARD_H
