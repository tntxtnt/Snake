#include <fstream>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include "conutils.h"
#include "Snake.h"
#include <ctime>
using namespace std;

const char *CELL_TYPE = " wfs";
const char DISP_CHR[] = { ' ', char(219), 'a', 'o', 'e', 'x' };
const int SNAKE_LEN = 5;

void initGrid(char**&,int,int);
void delGrid(char**&,int,int);
void loadGrid(char**&,int&,int&,const char*);
void printGrid(char**,int,int);
void quickPrint(const Snake&);
Coord putFood(char**,int,int,int&);

int main()
{
    srand(unsigned(time(NULL)));

    char **grid;
    int height;
    int width;
    int spaceCount = 0;
    int speed = 200;
    Coord food;

    //load map
    loadGrid(grid, height, width, "map2.txt");
    int scoreLine = height + 3;

    //put snake in
    Snake kk(grid, height, width, SNAKE_LEN);

    //count spaces
    for (int i = 1; i <= height; ++i)
        for (int j = 1; j <= width; ++j)
            spaceCount += grid[i][j] == NONE;

    //print grid
    printGrid(grid, height, width);
    //print head
    gotoxy(kk.getHead().x, kk.getHead().y);
    cout << DISP_CHR[SNK_HEAD];

    //put food in
    food = putFood(grid, height, width, spaceCount);
    gotoxy(food.x, food.y);
    cout << DISP_CHR[FOOD];

    //print score and speed
    gotoxy(0,scoreLine);
    cout << speed << "ms - Score: " << kk.length()-SNAKE_LEN;

    //game loop
    while (kk.isAlive())
    {
        Sleep(speed);
        int preLen = kk.length();
        //delete head
        Coord kkh = kk.getHead();
        gotoxy(kkh.x, kkh.y);
        cout << DISP_CHR[SNAKE];
        //move
        kk.detectDirection();
        kk.move();
        quickPrint(kk);

        if (kk.length() > preLen) //eat event
        {
            speed -= 30;
            if (speed < 70) speed = 200;

            //put in new food
            food = putFood(grid, height, width, spaceCount);
            gotoxy(food.x, food.y);
            cout << DISP_CHR[FOOD];

            gotoxy(0,scoreLine); //print new score
            cout << speed << "ms - Score: " << kk.length()-SNAKE_LEN;
        }
    }
    gotoxy(kk.getHead().x, kk.getHead().y);
    cout << DISP_CHR[SNAKE];
    gotoxy(kk.getCollision().x, kk.getCollision().y);
    cout << DISP_CHR[SNK_DEAD];

    //delete grid
    delGrid(grid, height, width);

    gotoxy(0,scoreLine+1);
    cin.sync();
    cin.get();
}

//cout << char(176) << char(177) << char(178) << char(219);

void initGrid(char**&grid, int height, int width)
{
    grid = new char*[height+2];
    for (int i=0; i<height+2; ++i)
        grid[i] = new char[width+2];

    for (int i=0; i<height+2; ++i)
        for (int j=0; j<width+2; ++j)
            grid[i][j] = (!i||!j||i==height+1||j==width+1) ? WALL : NONE;
}

void delGrid(char**&grid, int height, int width)
{
    for (int i=0; i<height+2; ++i)
        delete [] grid[i];
    delete [] grid;
}

void loadGrid(char**& grid, int& height, int& width, const char *filePath)
{
    fstream fin(filePath, ios::in);
    if (!fin) {cout<<"Cannot open map\n"; exit(1);}
    fin >> width;
    fin >> height;
    initGrid(grid, height, width);
    string line;
    for (int i=1; i<height && fin.good(); ++i)
    {
        getline(fin, line);
        for (int j=1; j<=width && unsigned(j)<line.length(); ++j)
            if (line[j-1] == CELL_TYPE[WALL])
                grid[i][j] = WALL;
    } fin.close();
}

void printGrid(char **grid, int height, int width)
{
    for (int i=0; i<height+2; ++i)
    {
        for (int j=0; j<width+2; ++j)
            cout << DISP_CHR[int(grid[i][j])];
        cout << endl;
    }
}

void quickPrint(const Snake& snake)
{
    Coord trail = snake.getTrail();
    Coord head = snake.getHead();
    gotoxy(head.x, head.y);
    cout << DISP_CHR[SNAKE];
    if (trail.x != -1 && (trail.x!=head.x || trail.y!=head.y))
    {
        gotoxy(trail.x, trail.y);
        cout << DISP_CHR[NONE];
    }
    gotoxy(head.x, head.y);
    cout << DISP_CHR[SNK_HEAD];
}

Coord putFood(char **grid, int height, int width, int& spaceCount)
{
    int fi = rand() % spaceCount + 1;
    Coord food(0,0);
    for (int i=1; (i<=height) && fi; ++i)
        for (int j=1; (j<=width) && fi; ++j)
            if (grid[i][j] == NONE)
                if (!--fi)
                {
                    grid[i][j] = FOOD;
                    food.x = j;
                    food.y = i;
                }
    --spaceCount;
    return food;
}
