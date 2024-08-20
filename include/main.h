#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define GRAVITY 1
#define OBSTACLE_WIDTH 80
#define OBSTACLE_GAP 200
#define OBSTACLE_SPEED 5
#define MAX_OBSTACLE 3
#define FLAP_STRENGTH -10

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAME_OVER
} GameStateType;

typedef struct {
    int x, y;
    int velocity;
} Bird;

typedef struct {
    int x;
    int gapY;
    int width;
    int height;
} Obstacle;

typedef struct {
    GameStateType currentState;
    Bird bird;
    SDL_Renderer *renderer;
    Obstacle obstacles[MAX_OBSTACLE];
} GameState;

void drawRectangle(GameState *state, int x, int y, int w, int h, SDL_Color color);
void initializeObstacles(GameState *state);
void updateObstacles(GameState *state);
void drawObstacles(GameState *state);
bool checkCollision(GameState *state);

#endif /** __MAIN_H__ */
