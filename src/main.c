#include "main.h"
#include "event_handler.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

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
    const char *title = "FlapGenius";
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Failed to create winddow: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return (1);
    }

    Bird bird = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0};
    GameState state = { STATE_MENU,
                        {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0} };
    printf("Bird and GameState initialized successfully.\n");

    SDL_bool gameIsActive = SDL_TRUE;
    SDL_Event e;

    while (gameIsActive) {
        gameIsActive = handleEvents(&e, &state);

        SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255);
        SDL_RenderClear(renderer);

        if (state.currentState == STATE_PLAYING) {
            state.bird.velocity += GRAVITY;
            state.bird.y += state.bird.velocity;

            SDL_Rect birdRect = { state.bird.x, state.bird.y, 50, 50 };
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &birdRect);
        } else if (state.currentState == STATE_MENU) {
            /**
             * TODO: Add actual menu rendering.
             */
        } else if (state.currentState == STATE_PAUSED) {
            /**
             * TODO: Add actual paused screen rendering
             */
        } else if (state.currentState == STATE_GAME_OVER) {
            /**
             * TODO: Add actual game over screen rendering
             */
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (0);
}