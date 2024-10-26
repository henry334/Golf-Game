/*
** PROJECT, 2024
** Assignement1
** File description:
** player
*/

#include "my.h"

Player *initPlayer(void)
{
    Player *player = (Player *)malloc(sizeof(Player));
    player->score = 0;
    player->stroke = 0;
    return player;
}
