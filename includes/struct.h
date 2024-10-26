/*
** PROJECT, 2024
** Assignement1
** File description:
** struct
*/

#pragma once

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct Vector2Int {
    int x;
    int y;
} Vector2Int;

typedef struct Wall {
    Vector2 pos1;
    Vector2 pos2;
    Vector2 pos3;
    Vector2 pos4;
    Vector2 size;
    unsigned int thickness;
    bool isMoving;
    float direction;
    float speed;
    bool isVertical;
} Wall;

typedef struct Ball {
    Vector2 pos;
    float vel;
    int radius;
    float deviationY;
} Ball;

typedef struct Player {
    int stroke;
    int number;
    int score;
} Player;

typedef struct Game {
    Player **players;
    Wall **walls;
    Ball ball;
    bool terrain2;
} Game;
