/* Tetrix color support by Eric S. Raymond, eric@snark.uu.net */

#include <curses.h>
#include "tet.h"

#ifdef A_COLOR
/* color pair indexes for pieces */
#define BLACK	0
#define GREEN	1
#define RED	2
#define TAN	3
#define WHITE	4
#define	VIOLET	5
#define BLUE	6
#define YELLOW	7
#define NCOLORS	8

static int attribs[NCOLORS];

typedef struct
{
    int	forgrnd;
    int attrib;
}
colorpair;

void init_colors(void)
{
    start_color();

    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    attribs[BLACK] = COLOR_PAIR(BLACK);

    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    attribs[GREEN] = COLOR_PAIR(GREEN);

    init_pair(RED, COLOR_RED, COLOR_BLACK);
    attribs[RED] = COLOR_PAIR(RED);

#ifdef EGA
    init_pair(TAN, COLOR_YELLOW, COLOR_BLACK);
#else
    init_pair(TAN, COLOR_CYAN, COLOR_BLACK);
#endif /* EGA */
    attribs[TAN] = COLOR_PAIR(TAN);

    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    attribs[WHITE] = COLOR_PAIR(WHITE);

    init_pair(VIOLET, COLOR_MAGENTA, COLOR_BLACK);
    attribs[VIOLET] = COLOR_PAIR(VIOLET);

    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    attribs[BLUE] = COLOR_PAIR(BLUE);

#ifdef EGA
    attribs[YELLOW] = attribs[TAN] | A_BOLD;
#else
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    attribs[YELLOW] = COLOR_PAIR(YELLOW);
#endif /* EGA */
}

void PUTCH(int x,int y,int z)
{ 
    switch(z)
    {
    case NO_CHAR: attron(attribs[WHITE]); break;
    case 'G': attron(attribs[GREEN]|A_REVERSE); break;
    case 'R': attron(attribs[RED]|A_REVERSE); break;
    case 'O': attron(attribs[TAN]|A_REVERSE); break;
    case 'W': attron(attribs[WHITE]|A_REVERSE); break;
    case 'V': attron(attribs[VIOLET]|A_REVERSE); break;
    case 'B': attron(attribs[BLUE]|A_REVERSE); break;
    case 'Y': attron(attribs[YELLOW]|A_REVERSE); break;
    }
    mvaddch(y, x, z);
    if (INBOARD(x, y))
	Board[x-MINX][y-MINY]=z;
    attrset(0);
}

#endif /* A_COLOR */
