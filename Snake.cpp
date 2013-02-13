#include "Snake.h"
#include <iostream>
#include <cstdlib>
#include "conutils.h"
#include <windows.h>

Snake::Snake(char **g, int h, int w, int len)
: alive(1), direction(RIGHT), trail(-1,-1), height(h), width(w)
{
    grid = g;
    if (len>width) len = width;
    for (int i=len; i>0; --i)
    {
        snake.push_back(Coord(i,height));
        grid[height][i] = SNAKE;
    }
}

Snake::~Snake()
{
}

void Snake::move()
{
    //get next coord
    Coord next(snake.front());
    if      (direction == UP)   --next.y;
    else if (direction == DOWN) ++next.y;
    else if (direction == LEFT) --next.x;
    else                        ++next.x;
    //move the body and tail
    trail = snake.back();
    for (int i = snake.size()-1; i > 0; --i)
        snake[i] = snake[i-1];
    //delete the trail on grid
    grid[trail.y][trail.x] = NONE;

    if (grid[next.y][next.x] == WALL || grid[next.y][next.x] == SNAKE)
    {
        alive = false;
        collision = next;
    }
    else if (grid[next.y][next.x] == FOOD)
    {
        snake[0] = next;
        grid[next.y][next.x] = SNAKE;
        //append a new part
        snake.push_back(trail);
        grid[trail.y][trail.x] = SNAKE;
        //wipe out trail
        trail.x = trail.y = -1;
    }
    else
    {
        snake[0] = next;
        grid[next.y][next.x] = SNAKE;
    }
}

void Snake::detectDirection()
{
    if      ((GetAsyncKeyState(0x65) || GetAsyncKeyState(VK_UP)) && direction != DOWN)
        direction = UP;
    else if ((GetAsyncKeyState(0x62) || GetAsyncKeyState(VK_DOWN)) && direction != UP)
        direction = DOWN;
    else if ((GetAsyncKeyState(0x61) || GetAsyncKeyState(VK_LEFT)) && direction != RIGHT)
        direction = LEFT;
    else if ((GetAsyncKeyState(0x63) || GetAsyncKeyState(VK_RIGHT)) && direction != LEFT)
        direction = RIGHT;
}
