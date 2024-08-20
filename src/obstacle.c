#include "main.h"

void initializeObstacles(GameState *state) {
    for (int i = 0; i < MAX_OBSTACLE; i++) {
        state->obstacles[i].x = SCREEN_WIDTH + i * (OBSTACLE_WIDTH + 200);
        state->obstacles[i].gapY = rand() % (SCREEN_HEIGHT - OBSTACLE_GAP);
        state->obstacles[i].width = OBSTACLE_WIDTH;
        state->obstacles[i].height = SCREEN_HEIGHT;
    }
}

void updateObstacles(GameState *state) {
    for (int i = 0; i < MAX_OBSTACLE; i ++) {
        state->obstacles[i].x -= OBSTACLE_SPEED;

        if (state->obstacles[i].x + state->obstacles[i].width < 0) {
            state->obstacles[i].x = SCREEN_WIDTH;
            state->obstacles[i].gapY = rand() % (SCREEN_HEIGHT - OBSTACLE_GAP);
        }
    }
}

void drawObstacles(GameState *state) {
    SDL_Color obstacleColor = {0, 255, 0, 255};

    for (int i = 0; i < MAX_OBSTACLE; i++) {
        drawRectangle(state, state->obstacles[i].x, 0, state->obstacles[i].width, state->obstacles[i].gapY, obstacleColor);
        drawRectangle(state, state->obstacles[i].x, state->obstacles[i].gapY + OBSTACLE_GAP, state->obstacles[i].width, SCREEN_HEIGHT - (state->obstacles[i].gapY + OBSTACLE_GAP), obstacleColor);
    }
}
