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

#define NUMBER_OF_PLAYERS 2
#define MAX_STROKE 40
#define PAUSE_TIME 30
#define PAUSE_TIME_BETWEEN_STROKES 1000

#define CANVAS_WIDTH 1000
#define CANVAS_HEIGHT 200
#define WALL_THICKNESS 2

#define HOLE_RADIUS 50
#define HOLE_X (CANVAS_WIDTH * 0.80)
#define HOLE_Y (CANVAS_HEIGHT / 2)

#define BALL_VELOCITY 19
#define BALL_RADIUS 25
#define BALL_START_POS_X (CANVAS_WIDTH * 0.10)
#define BALL_START_POS_Y (CANVAS_HEIGHT / 2)

#define FRICTION 0.90
#define DEVIATION 6
#define PERFECT_SHOT_CHANCE 2

void initCanvas(void);
int initGame(Game *);
int gameLoop(Game *);
Player *iniPlayer(void);
void displayGame(Player *, Game *);
void displayWin(Player *);
void displayEnd(Game *);
int returnBestPlayer(Player **);

// Collision
Wall *creatWall(Vector2Int, Vector2Int,  Vector2Int, Vector2Int, unsigned int);
bool isBallCollidingWithWall(Ball *, Wall *);
bool checkWallCollision(Ball *ball, Wall **walls);
bool isBallInHole(Ball *);
void addGameWall(Game *);
int checkShootDirection(Ball *);

// Free
void freePLayerList(Player **player);
void freeWallList(Wall **wall);