/*
** PROJECT, 2024
** Assignement1
** File description:
** game
*/

#include "my.h"

int initGame(Game *game) {
    game->ball = (Ball){{BALL_START_POS_X, BALL_START_POS_Y}, BALL_VELOCITY, BALL_RADIUS, 0};
    game->players = (Player **)malloc(sizeof(Player *) * (NUMBER_OF_PLAYERS + 1));
    for (unsigned int i = 0; i < NUMBER_OF_PLAYERS; i++) {
        Player *player = iniPlayer();
        player->number = i + 1;
        if (player == NULL)
            return 84;
        game->players[i] = player;
    }
    game->players[NUMBER_OF_PLAYERS] = NULL;
    return 0;
}

void initCanvas(void) {
    gd_resetCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    gd_setCanvasColor(GREEN);
}

double generateDeviation(double precision) {
    return ((double)rand() / RAND_MAX) * 2 * precision - precision;
}

bool moveBall(Player *player, Game *game) {
    Ball *ball = &game->ball;
    ball->pos.x += ball->vel;
    ball->pos.y += ball->deviationY;
    ball->vel *= FRICTION;
    if (ball->pos.x > HOLE_X) {
        ball->pos.x = BALL_START_POS_X;
        ball->pos.y = BALL_START_POS_Y;
        ball->vel = BALL_VELOCITY;
        player->score++;
        player->stroke = 0;
        ball->deviationY = 0;
        return true;
    }

    if (ball->vel <= 1.0000) {
        ball->vel = BALL_VELOCITY;
        player->stroke++;
        ball->deviationY = generateDeviation(PRECISION);
        gd_pause(PAUSE_TIME_BETWEEN_STROKES);
    }
    return false;
}


void playerTurn(Player *player, Game *game) {
    double deviation = generateDeviation(PRECISION);
    printf("dev: %f\n", deviation);
    game->ball.deviationY = deviation;
    while (player->stroke < MAX_STROKE) {
        displayGame(player, game);
        if (moveBall(player, game))
            break;
    }
}

int gameLoop(Game *game) {
    bool end = false;
    while (!end) {
        for (unsigned int i = 0; game->players[i] != NULL; i++) {
            Player *player = game->players[i];
            playerTurn(player, game);
            if (player->score >= WIN_SCORE) {
                displayWin(player);
                end = true;
                break;
            }
        }
    }
    return 0;
}
