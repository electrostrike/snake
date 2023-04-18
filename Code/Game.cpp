#include "Game.h"

Game::Game() {
    apple.GenerateApple(snake.GetSnake());
    highScore = 0;

    ifstream fi("resources/HighScore.txt");
    string line;
    while (getline(fi, line)) {
        highScore = stoi(line);
    }
    fi.close();
}

Game::~Game() {
    TTF_CloseFont(font);
    font = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    Mix_FreeChunk(moving);
    moving = NULL;
    Mix_FreeChunk(scoring);
    scoring = NULL;
    Mix_FreeChunk(gameOver);
    gameOver = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

bool Game::Init() {
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

bool Game::LoadMedia() {
    font = TTF_OpenFont("resources/PressStart2P-vaV7.ttf", 20);
    if (font == NULL)
    {
        cout << "Failed to load font\n";
        cout << "SDL_ttf error: " << TTF_GetError() << "\n";
        return 0;
    }
    moving = Mix_LoadWAV("resources/moving.mp3");
    if (moving == NULL)
    {
        cout << "Failed to load music\n";
        cout << "SDL_mixer error: " << Mix_GetError() << "\n";
        return 0;
    }
    scoring = Mix_LoadWAV("resources/scoring.mp3");
    if (scoring == NULL)
    {
        cout << "Failed to load music\n";
        cout << "SDL_mixer error: " << Mix_GetError() << "\n";
        return 0;
    }
    gameOver = Mix_LoadWAV("resources/gameOver.mp3");
    if (gameOver == NULL)
    {
        cout << "Failed to load music\n";
        cout << "SDL_mixer error: " << Mix_GetError() << "\n";
        return 0;
    }
    return 1;
}

void Game::Run() {
    if (!Init())
    {
        cout << "Failed to initialize";
        return;
    }

    srand(time(NULL));
    if (!LoadMedia()) {
        cout << "Failed to load media";
        return;
    }
    SDL_Event e;
    quit = 0;
    play = 0;
    sfx = 1;
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
                    case SDLK_r:
                        play = 1;
                        break;

                    default:
                        break;
                }
            }
        }
        SDL_RenderClear(renderer);
        board.FillBlack(renderer);
        board.DrawPressR(renderer, font);
        SDL_RenderPresent(renderer);

        if (play) {
            RunGame();
        }
    }
}

void Game::RunGame() {
    SDL_Event e;
    upTime = SDL_GetTicks();
    score = 0;
    while (play)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {
                quit = 1;
                play = 0;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                        if (snake.SetDir(UP) && sfx) {
                            Mix_PlayChannel(-1, moving, 0);
                        }
                        break;

                    case SDLK_DOWN:
                        if (snake.SetDir(DOWN) && sfx) {
                            Mix_PlayChannel(-1, moving, 0);
                        }
                        break;

                    case SDLK_LEFT:
                        if (snake.SetDir(LEFT) && sfx) {
                            Mix_PlayChannel(-1, moving, 0);
                        }
                        break;

                    case SDLK_RIGHT:
                        if (snake.SetDir(RIGHT) && sfx) {
                            Mix_PlayChannel(-1, moving, 0);
                        }
                        break;

                    case SDLK_m:
                        sfx = !sfx;
                        break;

                    default:
                        break;
                }
            }
        }

        SDL_RenderClear(renderer);
        board.DrawBoard(renderer, snake, apple);
        board.DrawUI(renderer, font, score, highScore);
        SDL_RenderPresent(renderer);

        if (SDL_GetTicks() > upTime + 150) {
            snake.MoveSnake(apple);
            if (snake.HandleCollision()) {
                if (sfx) {
                    Mix_PlayChannel(-1, gameOver, 0);
                }
                if (score == highScore) {
                    ofstream fo("resources/HighScore.txt");
                    fo << to_string(highScore);
                    fo.close();
                }
                play = 0;
            }
            if (snake.GetEatApple()) {
                if (sfx) {
                    Mix_PlayChannel(-1, scoring, 0);
                }
                apple.GenerateApple(snake.GetSnake());
                snake.SetEatApple();
                score++;
                if (score > highScore) {
                    highScore = score;
                }
            }
            upTime = SDL_GetTicks();
        }
    }

    while (!play && !quit) {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {
                quit = 1;
                play = 1;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_r:
                        play = 1;
                        snake.Init();
                        apple.GenerateApple(snake.GetSnake());
                        break;

                    default:
                        break;
                }
            }
        }

        SDL_RenderClear(renderer);
        board.DrawGameOver(renderer, snake);
        board.DrawPressR(renderer, font);
        board.DrawUI(renderer, font, score, highScore);
        SDL_RenderPresent(renderer);
    }
}
