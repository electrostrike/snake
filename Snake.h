#ifndef SNAKE_H
#define SNAKE_H

#include "Constant.h"
#include "Apple.h"

class Snake {
    private:
        Direction dir;
        deque <Point> snake;
        bool eatApple;

    public:
        Snake();
        bool GetEatApple();
        void SetEatApple();
        void SetDir(Direction newDir);
        int GetLength();
        deque <Point> GetSnake();

        void MoveSnake(Apple apple);
        void HandleCollision();
};

#endif // SNAKE_H
