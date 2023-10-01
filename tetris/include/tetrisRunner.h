#ifndef TETRIS_RUNNER
#define TETRIS_RUNNER

#include "tetris.h"

extern int curRenderedBoard[BOARDSIZE];

void initTetrisGame();
enum gameSignal handleTetrisTick();
enum gameSignal handleTetrisUserEvent(char c);
bool gameOverTetrisAnimation();
#endif