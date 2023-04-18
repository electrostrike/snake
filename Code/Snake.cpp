#include "Snake.h"

Snake::Snake() {
    Init();
}

void Snake::Init() {
    snake.clear();
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

bool Snake::SetDir(Direction newDir) {
    if (abs(dir - newDir) != 2) {
        dir = newDir;
        return 1;
    }
    return 0;
}

const deque <Point>& Snake::GetSnake() {
    return snake;
}

int Snake::GetLength() {
    return snake.size();
}

void Snake::MoveSnake(Apple& apple) {
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

bool Snake::HandleCollision() {
    // Out of bound
    Point head = snake.front();
    if (head.x < 0 || head.x == BOARD_WIDTH || head.y < 2 || head.y == BOARD_HEIGHT) {
        snake.pop_front();
        return 1;
    }
    // Self collision
    for (int i = 1; i < snake.size(); i++) {
        if (head == snake[i]) {
            snake.pop_front();
            return 1;
        }
    }
    return 0;
}
