/*
** PROJECT, 2024
** Assignement1
** File description:
** free
*/

#include "my.h"

void freePLayerList(Player **player) {
    if (player == NULL)
        return;
    for (unsigned int i = 0; player[i] != NULL; i++) {
        free(player[i]);
    }
    free(player);
}

void freeWallList(Wall **wall) {
    if (wall == NULL)
        return;
    for (unsigned int i = 0; wall[i] != NULL; i++) {
        free(wall[i]);
    }
    free(wall);
}