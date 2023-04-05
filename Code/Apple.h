#ifndef APPLE_H
#define APPLE_H

#include "Constant.h"

class Apple {
    private:
        Point apple;

    public:
        Apple();
        Point GetApple();

        void GenerateApple(deque <Point> snake);
};

#endif // APPLE_H
