#include "event_handler.h"

bool handleEvents(SDL_Event *e, GameState *state) {
    while (SDL_PollEvent(e)) {
        if (e->type == SDL_QUIT) {
            printf("Quit game!\n");
            return SDL_FALSE;
        }
        if (e->type == SDL_KEYDOWN) {
            switch (e->key.keysym.sym) {
                case SDLK_SPACE:
                    if (state->currentState == STATE_PLAYING) {
                        state->bird.velocity = FLAP_STRENGTH;
                    } else if (state->currentState == STATE_MENU) {
                        state->currentState = STATE_PLAYING;
                    } else if (state->currentState == STATE_GAME_OVER) {
                        state->currentState = STATE_PLAYING;
                        state->bird.y = SCREEN_HEIGHT / 2;
                        state->bird.velocity = 0;
                    }
                    break;
                case SDLK_p:
                    if (state->currentState == STATE_PLAYING) {
                        state->currentState = STATE_PAUSED;
                    } else if (state->currentState == STATE_PAUSED) {
                        state->currentState = STATE_PLAYING;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return SDL_TRUE;
}
