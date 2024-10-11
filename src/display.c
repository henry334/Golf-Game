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

void displayWall(void) {
    gd_setFillColor(BLACK);
    gd_quadFilled(
        0, 0,                         // x1, y1
        CANVAS_WIDTH, 0,              // x2, y2
        CANVAS_WIDTH, WALL_THICKNESS, // x3, y3
        0, WALL_THICKNESS             // x4, y4
    );

    // Bottom wall
    gd_quadFilled(
        0, CANVAS_HEIGHT - WALL_THICKNESS,         // x1, y1
        CANVAS_WIDTH, CANVAS_HEIGHT - WALL_THICKNESS, // x2, y2
        CANVAS_WIDTH, CANVAS_HEIGHT,               // x3, y3
        0, CANVAS_HEIGHT                           // x4, y4
    );

    // Left wall
    gd_quadFilled(
        0, 0,                         // x1, y1
        WALL_THICKNESS, 0,            // x2, y2
        WALL_THICKNESS, CANVAS_HEIGHT, // x3, y3
        0, CANVAS_HEIGHT              // x4, y4
    );

    // Right wall
    gd_quadFilled(
        CANVAS_WIDTH - WALL_THICKNESS, 0,          // x1, y1
        CANVAS_WIDTH, 0,                          // x2, y2
        CANVAS_WIDTH, CANVAS_HEIGHT,              // x3, y3
        CANVAS_WIDTH - WALL_THICKNESS, CANVAS_HEIGHT // x4, y4
    );
}

void displayGame(Player *player, Game *game) {
    Ball ball = game->ball;
    gd_clear();
    displayText(player);
    displayWall();
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