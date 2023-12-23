#include <stdbool.h>

#include "display.h"
#include "timer.h"
#include "gameWrapper.h"

struct timespec lastTick;
struct game *curSelectedGame;
int curGameWaitTick;
int startedGame;


uint8_t curGameBoard[BOARDSIZE];
uint8_t curGameBuffer[BOARDSIZE];

void loadNewGame(struct game *toLoad){
    curSelectedGame = toLoad;
    setGame(toLoad);

    curGameWaitTick = toLoad->tickMs;
    timeout(curGameWaitTick);

    startedGame = 1;
}

int main(){
    initDisplay();

    curSelectedGame = initGameStructs(&curGameBoard, &curGameBuffer);
    loadNewGame(curSelectedGame);

    while(1){
        // main game loop

        if(startedGame == 0 && curSelectedGame->handleTick() == gameOver){
            break;
        }

        drawBoard(curGameBoard);

        timeout(curGameWaitTick);
        saveTickTime(&lastTick);

        bool gameIsPaused = false;
        int pausedRemainingTime = 0;

        while(1){
            char c = getch();

            if(c == ERR){
                saveTickTime(&lastTick);
                break;
            }

            if(c == BINDING_LOAD_NEW_GAME){
                loadNewGame(curSelectedGame->nextGame);
                break;
            }

            if(c == BINDING_PAUSE_GAME){
                if(gameIsPaused){
                    gameIsPaused = false;
                    timeout(pausedRemainingTime);
                    continue;
                }else{
                    gameIsPaused = true;
                    pausedRemainingTime = checkTick(&lastTick, curGameWaitTick);
                    timeout(-1);
                    continue;
                }
            }

            if(gameIsPaused){
                continue;
            }

            
            enum gameSignal signal = curSelectedGame->handlePlayerInput(c);

            if(signal == skipTimer){
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