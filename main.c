#include "tetrisRunner.h"
#include "display.h"
#include "timer.h"


int main(){
    initDisplay();
    initGame();
    saveTickTime();
    drawBoard(curRenderedBoard);

    int startedGame = 1;

    timeout(TICK_MS);

    while(1){
        // main game loop

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
        napms(GAME_OVER_MS);
    }

    endwin();

    return 0;
}