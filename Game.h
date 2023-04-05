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
        SDL_Color textColor = {255, 255, 255};

        //Game
        int score, highScore;
        bool hasSFX, quit;
        Apple apple;
        Snake snake;
        Board board;

        //SFX
        Mix_Music* bgm;
        Mix_Chunk* scoring;
        Mix_Chunk* gameOver;

    public:
        Game();
        ~Game();

        SDL_Renderer* GetRenderer();

        void LoadMedia();
        void Run();
        bool Init();
};

#endif // GAME
