#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

enum Direction { UP, DOWN, LEFT, RIGHT };
enum CellType { NONE, WALL, FOOD, SNAKE, SNK_HEAD, SNK_DEAD };
struct Coord {
    int x,y;
    Coord(int x=0, int y=0) : x(x), y(y) {}
    Coord(const Coord& r) : x(r.x), y(r.y) {}
};

class Snake
{
public:
    Snake(char **g, int h, int w, int len);
    ~Snake();
    void move();
    bool isAlive() const { return alive; }
    int length() const { return snake.size(); }
    void detectDirection();
    Coord getTrail() const { return trail; }
    Coord getHead() const { return snake[0]; }
    Coord getCollision() const { return collision; }
private:
    std::vector<Coord> snake;
    bool alive;
    char **grid;
    Direction direction;
    Coord trail;
    Coord collision;
    int height;
    int width;
};

#endif // SNAKE_H
