#include "inc/tetrisRunner.h"
#include "inc/display.h"
#include "inc/timer.h"


int main(){
    initDisplay();
    initGame();
    saveTickTime();

    timeout(TICK_MS);

    while(1){
        // main game loop
        drawBoard(curRenderedBoard);

        if(!handleTick()){
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
    }

    napms(5000);
    endwin();

    return 0;
}