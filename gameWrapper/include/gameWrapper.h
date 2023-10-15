#ifndef GAMEWRAPPER_H
#define GAMEWRAPPER_H

#include <stdbool.h>
#include "settings.h"

#include "tetrisRunner.h"
#include "snekRunner.h"

#define NUM_GAMES 2
#define GAME_NAME_LEN 16

extern struct game *curSelectedGame;
extern int curGameBoard[BOARDSIZE];

struct game{
    struct game *prevGame;
    char gameName[GAME_NAME_LEN];
    void (*initGame)(int (*board)[BOARDSIZE]);
    enum gameSignal (*handlePlayerInput)(char);
    enum gameSignal (*handleTick)(void);
    bool (*gameOverAnimation)(void);
    int tickMs;
    struct game *nextGame;
};

void initGameStructs();
void setPrevGame();
void setNextGame();
void setGame(struct game *nextGame);

#endif