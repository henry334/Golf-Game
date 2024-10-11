/*
** EPITECH PROJECT, 2024
** Assignement1
** File description:
** struct
*/

#pragma once

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

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
    Ball ball;
} Game;