#ifndef TETRIS_RUNNER
#define TETRIS_RUNNER

#include "tetris.h"

enum gameEvent{continueRound, skipRound};
extern int curRenderedBoard[BOARDSIZE];

void initGame();
bool handleTick();
enum gameEvent handleUserEvent(char c);

#endif