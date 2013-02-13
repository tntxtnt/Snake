#include "conutils.h"

void gotoxy(int x, int y)
{
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hStdOut,coord);
}

void clrscr()
{
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStdOut,&csbi)) return;
    COORD startCoord = {0,0};
    DWORD dummy;
    FillConsoleOutputCharacter(hStdOut,
                               ' ',
                               csbi.dwSize.X * csbi.dwSize.Y,
                               startCoord,
                               &dummy);
    gotoxy(0,0);
}

int gettextcolor()
{
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStdOut,&csbi)) return 0;
	WORD wAttributes = csbi.wAttributes;
	return wAttributes%16;
}

int getbackcolor()
{
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStdOut,&csbi)) return 0;
	WORD wAttributes = csbi.wAttributes;
	return (wAttributes/16)%16;
}

void setcolor(ConsoleColor textColor, ConsoleColor backColor)
{
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;
    WORD wAttributes = ((WORD)backColor<<4) | (WORD)textColor;
	SetConsoleTextAttribute(hStdOut, wAttributes);
}

void settextcolor(ConsoleColor textColor)
{
    setcolor(textColor, ConsoleColor(getbackcolor()));
}

void setbackcolor(ConsoleColor backColor)
{
    setcolor(ConsoleColor(gettextcolor()), backColor);
}

std::ostream& operator<<(std::ostream& out, ConsoleColor c)
{
    out.flush();
    setcolor(c, ConsoleColor(getbackcolor()));
    return out;
}

std::istream& operator>>(std::istream& in, ConsoleColor c)
{
    std::cout.flush();
    setcolor(c, ConsoleColor(getbackcolor()));
    return in;
}
