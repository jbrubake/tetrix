#define NO_TYPE		0
#define NO_CHAR		' '
#define BRITE_CHAR	'$'

/* type numbers 1-3, 4-7, 9-11 etc represent the white, red, blue etc */
/* pieces at different rotations */
#define G_TYPE	4		/* Green pieces */
#define G_CHAR	'G'
#define R_TYPE	8		/* Red pieces */
#define R_CHAR	'R'
#define T_TYPE  12		/* Tan pieces */
#define T_CHAR	'O'
#define W_TYPE	16		/* White pieces */
#define W_CHAR	'W'
#define V_TYPE	20		/* Violet pieces */
#define V_CHAR	'V'
#define B_TYPE	24		/* Blue pieces */
#define B_CHAR	'B'
#define Y_TYPE	28		/* Yellow pieces */
#define Y_CHAR	'Y'

#define MINX 15		/* defines corner screen position */
#define MINY 1

#define BOARD_WIDE 10
#define BOARD_HIGH 20

#define MAXX BOARD_WIDE+MINX
#define MAXY BOARD_HIGH+MINY

#define INBOARD(x, y)	((y)>=MINY && (x)>=MINX && (x)<MAXX && (y)<MAXY)

#define STARTROW 1		/* defines starting position of pieces */
#define STARTCOL 5

#define NEXTROW	10
#define NEXTCOL	27
#define NEXT_WIDE 5
#define NEXT_HIGH 3

extern char Board[BOARD_WIDE][BOARD_HIGH];

#ifndef A_COLOR
/* Macros */
/* offset the character on screen by MINX and MINY */
#define PUTCH(x,y,z) {  mvaddch(y,x,z); if (INBOARD(x, y)) Board[x-MINX][y-MINY]=z; }
#else
extern void PUTCH();
extern void init_colors();
#endif /* A_COLOR */

#ifdef BIGCPP
/* test whether a square is empty and legal */
#define IS_FREE(x,y)	(INBOARD(x, y) && (Board[x-MINX][y-MINY] == NO_CHAR))
#else
extern int IS_FREE();
#endif /* BIGCPP */
