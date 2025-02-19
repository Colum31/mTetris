#ifndef SNEKRUNNER_H
#define SNEKRUNNER_H

#include <stdbool.h>
#include "settings.h"

void initSnekGame(uint8_t (*boardPtr)[BOARDSIZE], uint8_t (*bufferPtr)[BOARDSIZE]);
enum gameSignal handleUserSnek(char c);
enum gameSignal handleSnekTick();
bool gameOverAnimationSnek();
#endif