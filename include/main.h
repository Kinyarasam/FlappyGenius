#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define GRAVITY 1

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
    GameStateType currentState;
    Bird bird;
} GameState;

#endif /** __MAIN_H__ */
