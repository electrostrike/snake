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
        void Init();
        bool GetEatApple();
        void SetEatApple();
        bool SetDir(Direction newDir);
        int GetLength();
        const deque <Point>& GetSnake();

        void MoveSnake(Apple& apple);
        bool HandleCollision();
};

#endif // SNAKE_H
