#include <string.h>

#include "gameWrapper.h"

char gameNames[NUM_GAMES][GAME_NAME_LEN] = {"Tetris", "Snek"};
enum gameSignal (*handlePlayerInputFunctions[NUM_GAMES])(char) = {handleTetrisUserEvent, handleUserSnek};
enum gameSignal (*handleTickFunctions[NUM_GAMES])(void) = {handleTetrisTick, handleSnekTick};
void (*initGameFunctions[NUM_GAMES])(int (*board)[BOARDSIZE]) = {initTetrisGame, initSnekGame};
bool (*gameOverAnimationFunctions[NUM_GAMES])(void) = {gameOverTetrisAnimation, gameOverAnimationSnek};
int gameTicks[NUM_GAMES] = {TETRIS_TICK_MS, SNEK_TICK_MS};

struct game availableGames[NUM_GAMES];
struct game *curSelectedGame;
int curGameBoard[BOARDSIZE];


void initGameStructs(){
    struct game *firstGame;
    struct game *curGame;
    struct game *prevGame;

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

    curSelectedGame = firstGame;
}

void setPrevGame(){
    curSelectedGame = curSelectedGame->prevGame;
    curSelectedGame->initGame(&curGameBoard);
}

void setNextGame(){
    curSelectedGame = curSelectedGame->nextGame;
    curSelectedGame->initGame(&curGameBoard);
}

void setGame(struct game *nextGame){
    curSelectedGame = nextGame;
    curSelectedGame->initGame(&curGameBoard);
}
