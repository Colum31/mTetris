#define _POSIX_C_SOURCE 199309L

#include "settings.h"

long double diff_ms(struct timespec *start, struct timespec *end){
    long double startTimeMs = start->tv_sec * 1000.0 + start->tv_nsec / 1000000.0;
    long double endTimeMs = end->tv_sec * 1000.0 + end->tv_nsec / 1000000.0;

    return endTimeMs - startTimeMs;
}

int checkTick(struct timespec *lastTick, int tickTime){

    struct timespec curTick;
    clock_gettime(CLOCK_REALTIME, &curTick);

    int diff = (int) diff_ms(lastTick, &curTick);

    if(diff >= tickTime){
        return 0;
    }else{
        return tickTime - diff;
    }
}

void saveTickTime(struct timespec *tickToSave){
    clock_gettime(CLOCK_REALTIME, tickToSave);
}