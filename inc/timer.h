#ifndef TIMER_H
#define TIMER_H

long double diff_ms(struct timespec *start, struct timespec *end);
int checkTick();
void saveTickTime();

#endif