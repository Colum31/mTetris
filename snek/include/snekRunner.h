#ifndef SNEKRUNNER_H
#define SNEKRUNNER_H

#include "settings.h"

void initSnekGame();
enum gameSignal handleUserSnek(char c);
enum gameSignal handleSnekTick();
#endif