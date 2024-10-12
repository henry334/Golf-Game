/*
** PROJECT, 2024
** Assignement1
** File description:
** colision
*/

#include "my.h"

bool isBallCollidingWithWall(Ball *ball, Wall *wall)
{
    int ballRadius = ball->radius - 2;
    if ((ball->pos.x + ballRadius >= wall->pos1.x) && (ball->pos.x - ballRadius <= wall->pos2.x - wall->thickness) &&
        (ball->pos.y + ballRadius >= wall->pos1.y) && (ball->pos.y - ballRadius <= wall->pos3.y - wall->thickness))
        return true;
    return false;
}

bool checkWallCollision(Ball *ball, Wall **walls)
{
    for (unsigned int i = 0; walls[i] != NULL; i++) {
        if (isBallCollidingWithWall(ball, walls[i]))
            return true;
    }
    return false;
}

void generateRandomPosWall(Wall *wall)
{
    int xOffset = (rand() % CANVAS_WIDTH / 2) * (rand() % 2 == 0 ? 1 : -1);
    int yOffset = (rand() % CANVAS_HEIGHT) * (rand() % 2 == 0 ? 1 : -1);

    if (wall->pos1.x + xOffset <= 0 || wall->pos1.x + xOffset >= CANVAS_WIDTH)
        xOffset *= 0;
    if (wall->pos1.y + yOffset <= 0 || (wall->pos1.y + MOVING_WALL_HEIGHT) + yOffset >= CANVAS_HEIGHT)
        yOffset *= 0;

    wall->pos1.x += xOffset;
    wall->pos2.x += xOffset;
    wall->pos3.x += xOffset;
    wall->pos4.x += xOffset;

    wall->pos1.y += yOffset;
    wall->pos2.y += yOffset;
    wall->pos3.y += yOffset;
    wall->pos4.y += yOffset;

    // printf("x: %d, y: %d ", xOffset, yOffset);
    // printf("pos1.x: %d, pos1.y: %d\n", wall->pos1.x, wall->pos1.y);
}

Wall *creatWall(Vector2Int pos1, Vector2Int pos2,  Vector2Int pos3, Vector2Int pos4, unsigned int thickness, bool isMoving)
{
    Wall *wall = (Wall *)malloc(sizeof(Wall));
    wall->pos1 = pos1;
    wall->pos2 = pos2;
    wall->pos3 = pos3;
    wall->pos4 = pos4;
    wall->thickness = thickness;
    wall->isMoving = isMoving;
    wall->direction = rand() % 2 == 0 ? 1 : -1;
    wall->speed = MOVING_WALL_SPEED + (rand() % 3);
    if (isMoving)
        generateRandomPosWall(wall);
    return wall;
}

void debug(Ball *ball) {
    printf("ball x: %f, ball y: %f | ", ball->pos.x, ball->pos.y);
    printf("hole x: %f, hole x+:%f, hole y: %d, hole y+: %d | ", HOLE_X - 1, HOLE_X + HOLE_RADIUS + 1, HOLE_Y - 1, HOLE_Y + HOLE_RADIUS + 1);
    if ((ball->pos.x >= HOLE_X - 1 && ball->pos.x <= HOLE_X + HOLE_RADIUS + 1))
        printf("x is in ");
    if ((ball->pos.y >= HOLE_Y - 1 && ball->pos.y <= HOLE_Y + HOLE_RADIUS + 1))
        printf("y is in");
    printf("\n");
}

bool isBallInHole(Ball *ball)
{
    if (DEBUG)
        debug(ball);
    int v = (HOLE_RADIUS / 2);
    if ((ball->pos.x >= HOLE_X - v && ball->pos.x <= HOLE_X + v) &&
        (ball->pos.y >= HOLE_Y - v && ball->pos.y <= HOLE_Y + v))
        return true;
    return false;
}

void moveMovingWall(Game *game) {
    Wall **walls = game->walls;
    for (unsigned int i = 0; walls[i] != NULL; i++) {
        int movingSpeed = walls[i]->speed;
        if (!walls[i]->isMoving)
            continue;
        if (walls[i]->pos1.y < 0 || walls[i]->pos1.y + (MOVING_WALL_HEIGHT) >= CANVAS_HEIGHT)
            walls[i]->direction *= -1;
        walls[i]->pos1.y += (movingSpeed * walls[i]->direction);
        walls[i]->pos2.y += (movingSpeed * walls[i]->direction);
        walls[i]->pos3.y += (movingSpeed * walls[i]->direction);
        walls[i]->pos4.y += (movingSpeed * walls[i]->direction);
    }
}

void addGameWall(Game *game) {
    Wall **walls = (Wall **)malloc(sizeof(Wall *) * (5 + MOVING_WALL_NUMBER));
    walls[0] = creatWall((Vector2Int){0, 0}, (Vector2Int){CANVAS_WIDTH, 0}, (Vector2Int){CANVAS_WIDTH, WALL_THICKNESS}, (Vector2Int){0, WALL_THICKNESS}, WALL_THICKNESS, false);
    walls[1] = creatWall((Vector2Int){0, CANVAS_HEIGHT - WALL_THICKNESS}, (Vector2Int){CANVAS_WIDTH, CANVAS_HEIGHT - WALL_THICKNESS}, (Vector2Int){CANVAS_WIDTH, CANVAS_HEIGHT}, (Vector2Int){0, CANVAS_HEIGHT}, WALL_THICKNESS, false);
    walls[2] = creatWall((Vector2Int){0, 0}, (Vector2Int){WALL_THICKNESS, 0}, (Vector2Int){WALL_THICKNESS, CANVAS_HEIGHT}, (Vector2Int){0, CANVAS_HEIGHT}, WALL_THICKNESS, false);
    walls[3] = creatWall((Vector2Int){CANVAS_WIDTH - WALL_THICKNESS, 0}, (Vector2Int){CANVAS_WIDTH, 0}, (Vector2Int){CANVAS_WIDTH, CANVAS_HEIGHT}, (Vector2Int){CANVAS_WIDTH - WALL_THICKNESS, CANVAS_HEIGHT}, WALL_THICKNESS, false);
    int i;
    for (i = 4; i < 4 + MOVING_WALL_NUMBER; i++) {
        walls[i] = creatWall((Vector2Int){CANVAS_WIDTH / 2, 0}, (Vector2Int){CANVAS_WIDTH / 2 + WALL_THICKNESS, 0}, (Vector2Int){CANVAS_WIDTH / 2 + WALL_THICKNESS,  MOVING_WALL_HEIGHT}, (Vector2Int){CANVAS_WIDTH / 2, MOVING_WALL_HEIGHT}, WALL_THICKNESS, true);
    }
    walls[i] = NULL;
    game->walls = walls;
}

int checkShootDirection(Ball *ball)
{
    if (ball->pos.x >= HOLE_X + HOLE_RADIUS)
        return -1;
    return 1;
}