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
    if ((ball->pos.x + ballRadius >= wall->pos1.x) && (ball->pos.x - ballRadius < wall->pos2.x - wall->thickness)
        && (ball->pos.y + ballRadius >= wall->pos1.y) && (ball->pos.y - ballRadius < wall->pos3.y - wall->thickness)) {
            if (wall->isVertical) {
                ball->vel *= -1;
                ball->deviationY = 0;
                ball->pos.x += ball->vel;
            } else {
                ball->deviationY *= -1;
            }
            return true;
        }
    return false;
}

bool checkWallCollision(Ball *ball, Wall **walls)
{
    for (unsigned int i = 0; walls[i] != NULL; i++) {
        if (isBallCollidingWithWall(ball, walls[i])) {
            return true;
        }
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

Wall *creatWall(Vector2 pos1, Vector2 pos2,  Vector2 pos3, Vector2 pos4, unsigned int thickness, bool isMoving, bool isVertical)
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
    wall->isVertical = isVertical;
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

int getWallNumber(void) {
    if (RANDOM_WALL) {
        return rand() % MOVING_WALL_NUMBER;
    }
    return MOVING_WALL_NUMBER;
}

void addGameWall(Game *game) {
    int numberWall = getWallNumber();
    Wall **walls = (Wall **)malloc(sizeof(Wall *) * (5 + numberWall));
    walls[0] = creatWall((Vector2){0, 0}, (Vector2){CANVAS_WIDTH, 0}, (Vector2){CANVAS_WIDTH, WALL_THICKNESS}, (Vector2){0, WALL_THICKNESS}, WALL_THICKNESS, false, false);
    walls[1] = creatWall((Vector2){0, CANVAS_HEIGHT - WALL_THICKNESS}, (Vector2){CANVAS_WIDTH, CANVAS_HEIGHT - WALL_THICKNESS}, (Vector2){CANVAS_WIDTH, CANVAS_HEIGHT}, (Vector2){0, CANVAS_HEIGHT}, WALL_THICKNESS, false, false);
    walls[2] = creatWall((Vector2){0, 0}, (Vector2){WALL_THICKNESS, 0}, (Vector2){WALL_THICKNESS, CANVAS_HEIGHT}, (Vector2){0, CANVAS_HEIGHT}, WALL_THICKNESS, false, true);
    walls[3] = creatWall((Vector2){CANVAS_WIDTH - WALL_THICKNESS, 0}, (Vector2){CANVAS_WIDTH, 0}, (Vector2){CANVAS_WIDTH, CANVAS_HEIGHT}, (Vector2){CANVAS_WIDTH - WALL_THICKNESS, CANVAS_HEIGHT}, WALL_THICKNESS, false, true);
    int i;
    for (i = 4; i < 4 + numberWall; i++) {
        walls[i] = creatWall((Vector2){CANVAS_WIDTH / 2, 0}, (Vector2){CANVAS_WIDTH / 2 + MOVING_WALL_THICKNESS, 0}, (Vector2){CANVAS_WIDTH / 2 + MOVING_WALL_THICKNESS,  MOVING_WALL_HEIGHT}, (Vector2){CANVAS_WIDTH / 2, MOVING_WALL_HEIGHT}, MOVING_WALL_THICKNESS, true, true);
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