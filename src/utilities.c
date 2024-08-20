#include "main.h"

void drawRectangle(GameState *state, int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(state->renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(state->renderer, &rect);
}
