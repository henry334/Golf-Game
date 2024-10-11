/*
** PROJECT, 2024
** Assignement1
** File description:
** display
*/

#include "my.h"

void displayText(Player *player)
{
    gd_setTextAlignment(CENTER);
    gd_text("Player: ", 35, 10);
    gd_text(gd_to_string(player->number), 75, 10);
    gd_text("Stroke: ", 130, 10);
    gd_text(gd_to_string(player->stroke + 1), 170, 10);
    gd_text("Score: ", 32, 40);
    gd_text(gd_to_string(player->score), 75, 40);
}

void displayWall(Game *game) {
    gd_setFillColor(BLACK);
    Wall **walls = game->walls;
    for (unsigned int i = 0; walls[i] != NULL; i++) {
        Wall *wall = walls[i];
        gd_quadFilled(wall->pos1.x, wall->pos1.y, wall->pos2.x, wall->pos2.y, wall->pos3.x, wall->pos3.y, wall->pos4.x, wall->pos4.y);
    }
    
}

void displayGame(Player *player, Game *game) {
    Ball ball = game->ball;
    gd_clear();
    displayText(player);
    displayWall(game);
    gd_setFillColor(BLACK);
    gd_circleFilled(HOLE_X, HOLE_Y, HOLE_RADIUS);
    gd_setFillColor(WHITE);
    gd_circleFilled(ball.pos.x, ball.pos.y, ball.radius);
    gd_pause(PAUSE_TIME);
}

void displayWin(Player *player) {
    gd_clear();
    gd_text("Player: ", (CANVAS_WIDTH / 2) - 50, CANVAS_HEIGHT / 2);
    gd_text(gd_to_string(player->number), (CANVAS_WIDTH / 2) - 10, CANVAS_HEIGHT / 2);
    gd_text("Wins", (CANVAS_WIDTH / 2) + 20, CANVAS_HEIGHT / 2);
}

void displayLoose(void) {
    gd_clear();
    gd_text("No one wins", CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2);
}