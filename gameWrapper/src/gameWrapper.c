#include <string.h>

#include "gameWrapper.h"

char gameNames[NUM_GAMES][GAME_NAME_LEN] = {"Tetris", "Snek"};
enum gameSignal (*handlePlayerInputFunctions[NUM_GAMES])(char) = {handleTetrisUserEvent, handleUserSnek};
enum gameSignal (*handleTickFunctions[NUM_GAMES])(void) = {handleTetrisTick, handleSnekTick};
void (*initGameFunctions[NUM_GAMES])(uint8_t (*board)[BOARDSIZE], uint8_t (*buffer)[BOARDSIZE]) = {initTetrisGame, initSnekGame};
bool (*gameOverAnimationFunctions[NUM_GAMES])(void) = {gameOverTetrisAnimation, gameOverAnimationSnek};
int gameTicks[NUM_GAMES] = {TETRIS_TICK_MS, SNEK_TICK_MS};

struct game availableGames[NUM_GAMES];

uint8_t (*boardPtr)[BOARDSIZE];
uint8_t (*gameBufferPtr)[BOARDSIZE];

struct game *initGameStructs(uint8_t (*curBoardPtr)[BOARDSIZE], uint8_t (*curGameBufferPtr)[BOARDSIZE]){
    struct game *firstGame;
    struct game *curGame;
    struct game *prevGame;

    boardPtr = curBoardPtr;
    gameBufferPtr = curGameBufferPtr;

    for(int i = 0; i < NUM_GAMES; i++){

        curGame = &availableGames[i];

        strcpy(curGame->gameName, gameNames[i]);
        curGame->initGame = initGameFunctions[i];
        curGame->handlePlayerInput = handlePlayerInputFunctions[i];
        curGame->handleTick = handleTickFunctions[i];
        curGame->gameOverAnimation = gameOverAnimationFunctions[i];
        curGame->tickMs = gameTicks[i];

        if(i == 0){
            firstGame = curGame;
        }else{
            curGame->prevGame = prevGame;
            prevGame->nextGame = curGame;
        }

        prevGame = curGame;
    }

    // curGame contains last game
    curGame->nextGame = firstGame;
    firstGame->prevGame = curGame;

    return firstGame;
}

struct game *setPrevGame(struct game *curGame){
    struct game *prevGame = curGame->prevGame;
    prevGame->initGame(boardPtr, gameBufferPtr);
    return prevGame;
}

struct game *setNextGame(struct game *curGame){
    struct game *nextGame = curGame->nextGame;
    nextGame->initGame(boardPtr, gameBufferPtr);
    return nextGame;
}

struct game *setGame(struct game *curGame){
    curGame->initGame(boardPtr, gameBufferPtr);
    return curGame;
}
