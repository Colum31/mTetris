#include "display.h"
#include "timer.h"
#include "gameWrapper.h"


struct timespec lastTick;

int main(){
    initDisplay();
    saveTickTime(&lastTick);
    initGameStructs();

    curSelectedGame->initGame(&curGameBoard);
    int curGameWaitTick = curSelectedGame->tickMs;

    drawBoard(curGameBoard);

    int startedGame = 1;

    timeout(curGameWaitTick);

    while(1){
        // main game loop

        if(startedGame == 0 && curSelectedGame->handleTick() == gameOver){
            break;
        }

        drawBoard(curGameBoard);

        timeout(curGameWaitTick);
        saveTickTime(&lastTick);

        while(1){
            char c = getch();

            if(c == ERR){
                saveTickTime(&lastTick);
                break;
            }

            if(curSelectedGame->handlePlayerInput(c) == skipTimer){
                drawBoard(curGameBoard);
                break;
            }

            drawBoard(curGameBoard);

            int remainingTime = checkTick(&lastTick, curGameWaitTick);
            timeout(remainingTime);

        }

        startedGame = 0;
    }

    while(!curSelectedGame->gameOverAnimation()){
        drawBoard(curGameBoard);
        napms(GAME_OVER_MS);
    }

    endwin();

    return 0;
}