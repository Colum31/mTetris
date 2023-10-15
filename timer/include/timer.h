#ifndef TIMER_H
#define TIMER_H

#include <time.h>

int checkTick(struct timespec *lastTick, int tickTime);
void saveTickTime(struct timespec *tickToSave);

#endif