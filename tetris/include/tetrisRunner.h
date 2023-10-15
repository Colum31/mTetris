#ifndef TETRIS_RUNNER
#define TETRIS_RUNNER

#include "tetris.h"

void initTetrisGame(int (*boardPtr)[BOARDSIZE]);
enum gameSignal handleTetrisTick();
enum gameSignal handleTetrisUserEvent(char c);
bool gameOverTetrisAnimation();
#endif