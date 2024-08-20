#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "main.h"

#define FLAP_STRENGTH -10

bool handleEvents(SDL_Event *e, GameState *state);

#endif /** __EVENT_HANDLER_H__ */
