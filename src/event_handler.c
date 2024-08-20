#include "event_handler.h"

bool handleEvents(SDL_Event e) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            printf("Quit game!\n");
            return SDL_FALSE;
        }
    }
    return SDL_TRUE;
}
