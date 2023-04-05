#include "Board.h"

Board::Board() {

}

void Board::DrawBoard(SDL_Renderer* renderer, Snake snake, Apple apple) {
    //Draw board
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            SDL_Rect rect = {x * BOARD_UNIT, y * BOARD_UNIT, BOARD_UNIT, BOARD_UNIT};
            if ((x + y) & 1) {
                SDL_SetRenderDrawColor(renderer, GREEN_2.r, GREEN_2.g, GREEN_2.b, GREEN_2.a);
            } else {
                SDL_SetRenderDrawColor(renderer, GREEN_1.r, GREEN_1.g, GREEN_1.b, GREEN_1.a);
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Draw snake
    SDL_SetRenderDrawColor(renderer, BLUE.r, BLUE.g, BLUE.b, BLUE.a);
    deque <Point> mySnake = snake.GetSnake();
    for (Point body: mySnake) {
        SDL_Rect rect = {body.x * BOARD_UNIT, body.y * BOARD_UNIT, BOARD_UNIT, BOARD_UNIT};
        SDL_RenderFillRect(renderer, &rect);
    }

    // Draw apple
    SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a);
    SDL_Rect rect = {apple.GetApple().x * BOARD_UNIT, apple.GetApple().y * BOARD_UNIT, BOARD_UNIT, BOARD_UNIT};
    SDL_RenderFillRect(renderer, &rect);
}
