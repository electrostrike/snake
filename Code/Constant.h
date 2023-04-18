#ifndef CONSTANT_H
#define CONSTANT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <string>
#include <fstream>

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;

const int BOARD_UNIT = 20;
const int BOARD_WIDTH = 32; // WIDTH / 20
const int BOARD_HEIGHT = 24; // HEIGHT / 20

struct Point {
    int x, y;

    bool operator == (const Point& other) const {
        return x == other.x && y == other.y;
    }
};

enum Direction {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

const SDL_Color GREEN_1 = {168, 247, 120, 255};
const SDL_Color GREEN_2 = {158, 237, 110, 255};
const SDL_Color BLUE = {60, 108, 186, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color GRAY = {128, 128, 128, 255};

#endif // CONSTANT_H
