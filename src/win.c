/*
** PROJECT, 2024
** Assignement1
** File description:
** win
*/

#include "my.h"

int returnBestPlayer(Player **players)
{
    int best_score = 0;
    int best_player = 0;
    int stroke = MAX_STROKE;

    for (int i = 0; players[i] != NULL; i++) {
        if (players[i]->score >= best_score && players[i]->stroke < stroke) {
            best_score = players[i]->score;
            best_player = i;
            stroke = players[i]->stroke;
        }
    }
    return best_player;
}