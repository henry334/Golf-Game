/*
** PROJECT, 2024
** Assignement1
** File description:
** main
*/

#include "my.h"

int main(void)
{
    srand(time(NULL));
    Game game;
    int res = initGame(&game);
    if (res == 84) {
        printf("Error while initializing the game\n");
        return 84;
    }
    initCanvas();
    gameLoop(&game);
    gd_save("game.html");
    freePLayerList(game.players);
    freeWallList(game.walls);
    return 0;
}