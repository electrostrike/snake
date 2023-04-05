#include "Game.h"

Game::Game() {
    apple.GenerateApple(snake.GetSnake());
}

Game::~Game() {
//    TTF_CloseFont(font);
//    font = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

//    Mix_FreeMusic(bgm);
//    bgm = NULL;
//    Mix_FreeChunk(scoring);
//    scoring = NULL;
//    Mix_FreeChunk(gameOver);
//    gameOver = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

bool Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "Unable to initialize SDL\n";
        cout << "Error: " << SDL_GetError() << "\n";
        return 0;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			cout << "Warning: Linear texture filtering not enabled\n";
		}
        window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            cout << "Unable to initialize Window\n";
            cout << "Error: " << SDL_GetError() << "\n";
            return 0;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            int IMGFlag = IMG_INIT_PNG;
            if (!(IMG_Init(IMGFlag) & IMGFlag)) {
                cout << "Unable to initialize SDL_image\n";
                cout << "Error: " << IMG_GetError() << "\n";
                return 0;
            }
            if (TTF_Init() == -1) {
                cout << "Unable to initialize SDL_ttf\n";
                cout << "Error: " << TTF_GetError() << "\n";
                return 0;
            }
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                cout << "SDL_mixer could not initialize\n";
                cout << "Error: " << Mix_GetError() << "\n";
                return 0;
            }
        }
    }
    return 1;
}

void Game::LoadMedia() {

}

void Game::Run()
{
    if (!Init())
    {
        cout << "Failed to initialize";
        return;
    }

    srand(time(NULL));
    LoadMedia();
    SDL_Event e;
    int upTime = SDL_GetTicks();
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = 1;
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                        snake.SetDir(UP);
                        break;

                    case SDLK_DOWN:
                        snake.SetDir(DOWN);
                        break;

                    case SDLK_LEFT:
                        snake.SetDir(LEFT);
                        break;

                    case SDLK_RIGHT:
                        snake.SetDir(RIGHT);
                        break;

                    default:
                        break;
                }
            }
        }

        SDL_RenderClear(renderer);
        board.DrawBoard(renderer, snake, apple);
        SDL_RenderPresent(renderer);

        if (SDL_GetTicks() > upTime + 200) {
            snake.MoveSnake(apple);
            snake.HandleCollision();
            if (snake.GetEatApple()) {
                apple.GenerateApple(snake.GetSnake());
                snake.SetEatApple();
            }
            upTime = SDL_GetTicks();
        }
    }
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}
