/*
** PROJECT, 2024
** Assignement1
** File description:
** game
*/

#include "my.h"

int initGame(Game *game) {
    addGameWall(game);
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

void setDeviation(Ball *ball) {
    double deviation = generateDeviation(DEVIATION);
    if (rand() % (PERFECT_SHOT_CHANCE + 1) == 0 )
        deviation = 0;
    printf("deviation: %f\n", deviation);
    ball->deviationY = deviation;
}

void resetBall(Ball *ball) {
    ball->pos.x = BALL_START_POS_X;
    ball->pos.y = BALL_START_POS_Y;
    ball->vel = BALL_VELOCITY;
    ball->deviationY = 0;
}

bool moveBall(Player *player, Game *game) {
    Ball *ball = &game->ball;
    ball->pos.x += ball->vel;
    ball->pos.y += ball->deviationY;
    ball->vel *= FRICTION;

    if (isBallInHole(ball)) {
        player->score++;
        return true;
    }

    if (checkWallCollision(ball, game->walls)) {
        ball->vel *= -1;
        ball->deviationY *= -1;
    }

    if ((ball->vel >= 0 && ball->vel <= 1.0000) || (ball->vel <= 0 && ball->vel >= -1.0000)) {
        ball->vel = BALL_VELOCITY;
        player->stroke++;
        setDeviation(ball);
        gd_pause(PAUSE_TIME_BETWEEN_STROKES);
    }
    return false;
}

void playerTurn(Player *player, Game *game) {
    setDeviation(&game->ball);
    while (player->stroke < MAX_STROKE) {
        // for (unsigned int i = 0; i < game->players[i] != NULL; i++)
        displayGame(player, game);
        if (moveBall(player, game))
            break;
    }
    player->stroke = 0;
    resetBall(&game->ball);
}

int gameLoop(Game *game) {
    unsigned int end = 0;
    while (end < MAX_PLAY_PER_PLAYER) {
        for (unsigned int i = 0; game->players[i] != NULL; i++) {
            Player *player = game->players[i];
            printf("Player %d\n", player->number);
            playerTurn(player, game);
            if (player->score >= WIN_SCORE) {
                displayWin(player);
                return 0;
            }
        }
        end++;
    }
    displayLoose(); 
    return 0;
}
