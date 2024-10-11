/*
** EPITECH PROJECT, 2024
** Assignement1
** File description:
** my
*/

#pragma once
#include <stddef.h>
#include <time.h>
#include "geodraw.h"
#include "struct.h"


#define WIN_SCORE 1
#define NUMBER_OF_PLAYERS 2
#define MAX_STROKE 4
#define PAUSE_TIME 25
#define PAUSE_TIME_BETWEEN_STROKES 300

#define CANVAS_WIDTH 1000
#define CANVAS_HEIGHT 200
#define WALL_THICKNESS 2

#define HOLE_RADIUS 50
#define HOLE_X (CANVAS_WIDTH * 0.80)
#define HOLE_Y (CANVAS_HEIGHT / 2)

#define BALL_VELOCITY 45
#define BALL_RADIUS 25
#define BALL_START_POS_X (CANVAS_WIDTH * 0.10)
#define BALL_START_POS_Y (CANVAS_HEIGHT / 2)

#define FRICTION 0.75
#define DEVIATION 3
#define PERFECT_SHOT_CHANCE 0

void initCanvas(void);
int initGame(Game *);
int gameLoop(Game *);
Player *iniPlayer(void);
void displayGame(Player *, Game *);
void displayWin(Player *);
void displayLoose(void);

//free
void freePLayerList(Player **player);