/*
** PROJECT, 2024
** Assignement1
** File description:
** free
*/

#include "my.h"

void freePLayerList(Player **player) {
    for (unsigned int i = 0; player[i] != NULL; i++) {
        free(player[i]);
    }
    free(player);
}