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
    game->terrain2 = false;
    if (rand() % CHANCE_TO_GET_TERRAIN_2 == 0)
        game->terrain2 = true;
    addGameWall(game);
    initBall(game);
    game->players = (Player **)malloc(sizeof(Player *) * (NUMBER_OF_PLAYERS + 1));
    for (unsigned int i = 0; i < NUMBER_OF_PLAYERS; i++) {
        Player *player = initPlayer();
        player->number = i + 1;
        if (player == NULL)
            return 84;
        game->players[i] = player;
    }
    game->players[NUMBER_OF_PLAYERS] = NULL;
    return 0;
}

void initCanvas(Game *game) {
    gd_resetCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    if (game->terrain2) {
        gd_setCanvasColor(COLOR_TERRAIN_2);
    } else
        gd_setCanvasColor(COLOR_TERRAIN_1);
}

void setDeviation(Ball *ball) {
    double deviation = generateDeviation(DEVIATION);
    if (rdN(PERFECT_SHOT_CHANCE) == 0 )
        deviation = 0;
    // printf("deviation: %f\n", deviation);
    ball->deviationY = deviation;
}

bool moveBall(Player *player, Game *game) {
    Ball *ball = &game->ball;
    ball->pos.x += ball->vel;
    ball->pos.y += ball->deviationY;
    ball->vel *= game->terrain2 ? FRICTION_TERRAIN_2 : FRICTION_TERRAIN_1;
    ball->deviationY *= game->terrain2 ? FRICTION_TERRAIN_2 : FRICTION_TERRAIN_1;

    if (DEBUG) printf("player %d stroke: %d | ", player->number , player->stroke);
    if (isBallInHole(ball)) {
        player->score++;
        return true;
    }

    checkWallCollision(ball, game->walls);

    if (ball->vel > -1.0000 && ball->vel < 1.0000) {
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
        moveMovingWall(game);
        displayGame(player, game);
        if (moveBall(player, game))
            break;
    }
    initBall(game);
}

int gameLoop(Game *game) {
    for (unsigned int i = 0; game->players[i] != NULL; i++) {
        Player *player = game->players[i];
        playerTurn(player, game);
    }
    displayEnd(game); 
    return 0;
}
