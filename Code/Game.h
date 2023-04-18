#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Board.h"
#include "Apple.h"
#include "Constant.h"

class Game {
    private:
        //Window
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;

        //Game
        int score, highScore, upTime;
        bool quit, play, sfx;
        Apple apple;
        Snake snake;
        Board board;

        //SFX
        Mix_Chunk* moving;
        Mix_Chunk* scoring;
        Mix_Chunk* gameOver;

    public:
        Game();
        ~Game();

        bool Init();
        bool LoadMedia();
        void Run();
        void RunGame();
};

#endif // GAME
