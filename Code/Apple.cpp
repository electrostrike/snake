#include "Apple.h"

Apple::Apple() {
    srand(time(NULL));
}

Point Apple::GetApple() {
    return apple;
}

void Apple::GenerateApple(deque <Point> snake) {
    bool tile[BOARD_WIDTH][BOARD_HEIGHT];
    memset(tile, 0, sizeof(tile));
    for (Point body: snake) {
        tile[body.x][body.y] = 1;
    }
    int pos = rand() % (BOARD_WIDTH * (BOARD_HEIGHT - 2) - snake.size());
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 2; y < BOARD_HEIGHT; y++) {
            if (!tile[x][y]) {
                pos--;
                if (pos < 0) {
                    apple = {x, y};
                    return ;
                }
            }
        }
    }
}
