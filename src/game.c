/*
** PROJECT, 2024
** Assignement1
** File description:
** game
*/

#include "my.h"

int rdN(int n) {
    return rand() % n + 1;
}

double generateDeviation(double precision) {
    return ((double)rand() / RAND_MAX) * 2 * precision - precision;
}

void initBall(Game *game) {
    float x = BALL_START_POS_X + (float)generateDeviation(5);
    float y = BALL_START_POS_Y + (float)generateDeviation(5);
    float vel = BALL_VELOCITY + (float)generateDeviation(3);
    game->ball = (Ball){{x, y}, vel, BALL_RADIUS, 0};
}

int initGame(Game *game) {
    addGameWall(game);
    initBall(game);
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


void setDeviation(Ball *ball) {
    double deviation = generateDeviation(DEVIATION);
    if (rdN(PERFECT_SHOT_CHANCE) == 0 )
        deviation = 0;
    printf("deviation: %f\n", deviation);
    ball->deviationY = deviation;
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
        ball->vel = BALL_VELOCITY * checkShootDirection(ball);
        player->stroke++;
        setDeviation(ball);
        gd_pause(PAUSE_TIME_BETWEEN_STROKES);
    }
    return false;
}

void playerTurn(Player *player, Game *game) {
    setDeviation(&game->ball);
    while (player->stroke < MAX_STROKE) {
        displayGame(player, game);
        if (moveBall(player, game))
            break;
    }
    initBall(game);
}

int gameLoop(Game *game) {
    for (unsigned int i = 0; game->players[i] != NULL; i++) {
        Player *player = game->players[i];
        printf("Player %d\n", player->number);
        playerTurn(player, game);
    }
    displayEnd(game); 
    return 0;
}
