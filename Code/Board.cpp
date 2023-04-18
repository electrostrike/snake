#include "Board.h"

Board::Board() {

}

void Board::DrawBoard(SDL_Renderer* renderer, Snake& snake, Apple& apple) {
    FillBlack(renderer);

    //Draw board
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            SDL_Rect rect = {x * BOARD_UNIT, (y + 2) * BOARD_UNIT, BOARD_UNIT, BOARD_UNIT};
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
    auto mySnake = snake.GetSnake();
    for (Point body: mySnake) {
        SDL_Rect rect = {body.x * BOARD_UNIT, body.y * BOARD_UNIT, BOARD_UNIT, BOARD_UNIT};
        SDL_RenderFillRect(renderer, &rect);
    }

    // Draw apple
    SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a);
    SDL_Rect rect = {apple.GetApple().x * BOARD_UNIT, apple.GetApple().y * BOARD_UNIT, BOARD_UNIT, BOARD_UNIT};
    SDL_RenderFillRect(renderer, &rect);
}

void Board::DrawGameOver(SDL_Renderer* renderer, Snake& snake) {
    FillBlack(renderer);

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            SDL_Rect rect = {x * BOARD_UNIT, (y + 2) * BOARD_UNIT, BOARD_UNIT, BOARD_UNIT};
            if ((x + y) & 1) {
                SDL_SetRenderDrawColor(renderer, GREEN_2.r, GREEN_2.g, GREEN_2.b, GREEN_2.a);
            } else {
                SDL_SetRenderDrawColor(renderer, GREEN_1.r, GREEN_1.g, GREEN_1.b, GREEN_1.a);
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_SetRenderDrawColor(renderer, GRAY.r, GRAY.g, GRAY.b, GRAY.a);
    auto mySnake = snake.GetSnake();
    for (Point body: mySnake) {
        SDL_Rect rect = {body.x * BOARD_UNIT, body.y * BOARD_UNIT, BOARD_UNIT, BOARD_UNIT};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Board::DrawUI(SDL_Renderer* renderer, TTF_Font* font, int score, int highScore) {
    Texture scoreText;
    scoreText.LoadText(renderer, "SCORE: " + to_string(score), WHITE, font);
    scoreText.RenderTexture(renderer, 10, 10);

    Texture highScoreText;
    highScoreText.LoadText(renderer, "HIGH SCORE: " + to_string(highScore), WHITE, font);
    highScoreText.RenderTexture(renderer, WIDTH / 2 - 40, 10);
}

void Board::DrawPressR(SDL_Renderer* renderer, TTF_Font* font) {
    Texture pressR;
    pressR.LoadText(renderer, "PRESS R TO PLAY", WHITE, font);
    pressR.RenderTexture(renderer, WIDTH / 2 - 140, HEIGHT / 2 - 10);
}

void Board::FillBlack(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_Rect fillBlack = {0, 0, WIDTH, HEIGHT};
    SDL_RenderFillRect(renderer, &fillBlack);
}
