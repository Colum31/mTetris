#include "inc/tetrisRunner.h"
#include "inc/display.h"
#include "inc/timer.h"


int main(){
    initDisplay();
    initGame();
    saveTickTime();

    int startedGame = 1;

    timeout(TICK_MS);

    while(1){
        // main game loop
        drawBoard(curRenderedBoard);

        if(startedGame == 0 && !handleTick()){
            break;
        }

        drawBoard(curRenderedBoard);

        timeout(TICK_MS);
        saveTickTime();

        while(1){
            char c = getch();

            if(c == ERR){
                saveTickTime();
                break;
            }

            if(handleUserEvent(c) == skipRound){
                drawBoard(curRenderedBoard);
                break;
            }

            drawBoard(curRenderedBoard);

            int remainingTime = checkTick();
            timeout(remainingTime);

        }

        startedGame = 0;
    }

    while(!gameOverAnimation()){
        drawBoard(curRenderedBoard);
        napms(250);
    }

    napms(250);
    endwin();

    return 0;
}