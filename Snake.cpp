#include "Snake.h"

Snake::Snake() {
    snake.push_front({15, 11});
    snake.push_front({16, 11});
    snake.push_front({17, 11});
    snake.push_front({18, 11});
    dir = RIGHT;
    eatApple = false;
}

bool Snake::GetEatApple() {
    return eatApple;
}

void Snake::SetEatApple() {
    eatApple = !eatApple;
}

void Snake::SetDir(Direction newDir) {
    dir = newDir;
}

deque <Point> Snake::GetSnake() {
    return snake;
}

int Snake::GetLength() {
    return snake.size();
}

void Snake::MoveSnake(Apple apple) {
    Point newHead = snake.front();
    if (dir == UP) {
        newHead.y--;
    } else if (dir == DOWN) {
        newHead.y++;
    } else if (dir == LEFT) {
        newHead.x--;
    } else { // dir == RIGHT
        newHead.x++;
    }
    snake.push_front(newHead);
    if (apple.GetApple() == newHead) {
        eatApple = true;
    } else {
        snake.pop_back();
    }
}

void Snake::HandleCollision() {
    // Out of bound
    Point head = snake.front();
    if (head.x < 0 || head.x == BOARD_WIDTH || head.y < 0 || head.y == BOARD_HEIGHT) {
        exit(0);
    }
    // Self collision
    for (int i = 1; i < snake.size(); i++) {
        if (head == snake[i]) {
            exit(0);
        }
    }
}
