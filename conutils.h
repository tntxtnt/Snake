#ifndef CONSOLEULTILITIES_H
#define CONSOLEULTILITIES_H

#include <windows.h>
#include <iostream>

enum ConsoleColor
{
	BLACK=0,
	DARK_BLUE=1,
	DARK_GREEN=2,
	DARK_AQUA,DARK_CYAN=3,
	DARK_RED=4,
	DARK_PURPLE=5,DARK_PINK=5,DARK_MAGENTA=5,
	DARK_YELLOW=6,
	DARK_WHITE=7,
	GRAY=8,GREY=8,
	BLUE=9,
	GREEN=10,
	AQUA=11,CYAN=11,
	RED=12,
	PURPLE=13,PINK=13,MAGENTA=13,
	YELLOW=14,
	WHITE=15
};

void gotoxy(int x, int y);
void clrscr();

void setcolor(ConsoleColor textColor, ConsoleColor backColor);
int gettextcolor();
int getbackcolor();
void settextcolor(ConsoleColor textColor);
void setbackcolor(ConsoleColor backColor);
std::ostream& operator<<(std::ostream& out, ConsoleColor c);
std::istream& operator>>(std::istream& in, ConsoleColor c);

#endif // CONSOLEFUNCTIONS_H
