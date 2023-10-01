#ifndef SNEKRUNNER_H
#define SNEKRUNNER_H

#include <stdbool.h>
#include "settings.h"

extern int curRenderedSnekBoard[BOARDSIZE];

void initSnekGame();
enum gameSignal handleUserSnek(char c);
enum gameSignal handleSnekTick();
bool gameOverAnimationSnek();
#endif