#include "main.h"
#include "event_handler.h"
#include <stdbool.h>

void renderText(GameState *state, const char *text, int x, int y, int w, int h) {
    TTF_Font *font = TTF_OpenFont("assets/default.ttf", 28);
    if (!font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return;
    }

    SDL_Color color = {255, 0, 0};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(state->renderer, surface);

    SDL_Rect textRect = {x, y, w, h};
    SDL_RenderCopy(state->renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

/**
 * main - Entry point
 * 
 * Returns: Always 0 (success)
 *          otherwise 1.
 */
int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "failed to initialize SDL: %s\n", SDL_GetError());
    }
    if (TTF_Init() != 0) {
        fprintf(stderr, "Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return (1);
    }

    const char *title = "FlapGenius";
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Failed to create winddow: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return (1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return (1);
    }

    Bird bird = {SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2, 0};
    GameState state = {
        .currentState = STATE_MENU,
        .bird = bird,
        .renderer = renderer
    };

    initializeObstacles(&state);

    SDL_bool gameIsActive = SDL_TRUE;
    SDL_Event e;

    while (gameIsActive) {
        gameIsActive = handleEvents(&e, &state);

        SDL_SetRenderDrawColor(state.renderer, 135, 206, 250, 255);
        SDL_RenderClear(state.renderer);

        if (state.currentState == STATE_PLAYING) {
            state.bird.velocity += GRAVITY;
            state.bird.y += state.bird.velocity;

            if (state.bird.y + 50 >= SCREEN_HEIGHT) {
                state.bird.y = SCREEN_HEIGHT - 50;
                state.bird.velocity = 0;
                state.currentState = STATE_GAME_OVER;
            } else if (state.bird.y < 0) {
                state.bird.y = 0;
                state.bird.velocity = 0;
            }

            updateObstacles(&state);
            drawObstacles(&state);

            SDL_Color birdColor = {255, 255, 255, 255};
            drawRectangle(&state, state.bird.x, state.bird.y, 50, 50, birdColor);
        } else if (state.currentState == STATE_MENU) {
            /**
             * TODO : Add actual menu rendering.
             */
        } else if (state.currentState == STATE_PAUSED) {
            /**
             * TODO: Add actual paused screen rendering
             */
        } else if (state.currentState == STATE_GAME_OVER) {
            renderText(&state, "Game Over", SCREEN_HEIGHT / 4, SCREEN_WIDTH / 3, SCREEN_WIDTH / 2, 100);
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
                state.currentState = STATE_PLAYING;
                state.bird.y = SCREEN_HEIGHT / 2;
                state.bird.velocity = 0;
                initializeObstacles(&state);
            }
        }

        SDL_RenderPresent(state.renderer);
    }

    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return (0);
}