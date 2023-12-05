#ifndef GAMEWRAPPER_H
#define GAMEWRAPPER_H

#include <stdbool.h>
#include "settings.h"

#include "tetrisRunner.h"
#include "snekRunner.h"

#define NUM_GAMES 2
#define GAME_NAME_LEN 16

struct game{
    struct game *prevGame;
    char gameName[GAME_NAME_LEN];
    void (*initGame)(uint8_t (*board)[BOARDSIZE], uint8_t (*buffer)[BOARDSIZE]);
    enum gameSignal (*handlePlayerInput)(char);
    enum gameSignal (*handleTick)(void);
    bool (*gameOverAnimation)(void);
    int tickMs;
    struct game *nextGame;
};

struct game* initGameStructs(uint8_t (*boardPtr)[BOARDSIZE], uint8_t (*curGameBufferPtr)[BOARDSIZE]);
struct game *setPrevGame(struct game *curGame);
struct game *setNextGame(struct game *curGame);
struct game *setGame(struct game *curGame);

#endif