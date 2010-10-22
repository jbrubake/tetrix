/* Tetrix by quentin */

#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "tet.h"

/*
 * Good on a 2GHz Intel Core2 Duo in 2010.
 * Adjust upwards as technology advances.
 * As a matter of historical interest here
 * are the historical values for "reasonable:
 * 2010 = 200000
 * 2003 = 75000
 * 1994 = 150
 */
#define DEFAULT_INITPAUSE	200000

#define PAUSE_DECREMENT		(DEFAULT_INITPAUSE / 150)


#define HIGHCOUNT	10	/* count of high scorers to show */
#define SCORELEN	10	/* max length of score string */
#define NAMELEN		10	/* max length of user name string */

/********** Some global variable declarations ************/
static int Pause;		/* Time between movements this block */
static int InitPause;		/* Initial value of CurrentPause */
static int CurrentPause;	/* Time between movements per level */
static int FallingDown;		/* True when space bar is pressed */
static int Beep;		/* Beep on invalid move? */
static int Key;			/* holds last key polled */

int dispchars[6]
# ifdef IBMASCIZ
	= {0263,0304,0332,0277,0300,0331};
#else
	= {'|', '-', '.', '.', '`', '\''};
# endif /* IBMASCIZ */
# define VERT	dispchars[0]	/* vertical wall	*/
# define HORIZ	dispchars[1]	/* horizontal wall	*/
# define ULC	dispchars[2]	/* upper left corner	*/
# define URC	dispchars[3]	/* upper right corner	*/
# define LLC	dispchars[4]	/* lower left corner	*/
# define LRC	dispchars[5]	/* lower right corner	*/

#define SCORE_FILE	"/usr/tmp/.TetScores"
char ScoreString[SCORELEN];
struct ScoreStruct {
	char Name[NAMELEN];
	int Score;
} High[HIGHCOUNT];
int ThisScore,HighsChanged;
		
char Board[BOARD_WIDE][BOARD_HIGH];
char Temp[BOARD_WIDE][BOARD_HIGH];	/* temp storage for TestRows */

/* debug flash to screen */
#define FLASHMSG(x)
/*
#define FLASHMSG(x)	      { mvaddstr(23,0,"                "); \
				mvaddstr(23,0,x); \
				refresh(); }
*/
#define UPSCORE(x)    { ThisScore += x; \
			sprintf((char *)ScoreString,"%06d",ThisScore); \
			mvaddstr(1,46,ScoreString); }

#define NULL_KEY	'\0'
#define FALL_KEY	' '
#define RIGHT_KEY	'l'
#define LEFT_KEY	'j'
#define ROTATE_KEY	'k'
#define L_RIGHT_KEY	'f'		/* for south paws */
#define L_LEFT_KEY	's'
#define L_ROTATE_KEY	'd'
#define QUIT_KEY	'q'
#define BEEP_KEY	'b'
#define BOSS_KEY	'\033'
#define PLAY_KEY	'p'
#define SCORE_KEY	'h'
#define MENU_KEY	'm'

/*************************************************************/
Init(void)
{
	register char *ttnam, *p;
	register int x,y,i,fd;
	int timein;

	time(&timein);		/* get start time */
	srand48(timein);	/* start rand randomly */

	signal(SIGINT, SIG_IGN);
	
	Beep=0;
	HighsChanged = 0;
	initscr();
#ifdef KEY_MIN
	keypad(stdscr, TRUE);
	curs_set(0);
#endif /* KEY_MIN */
	nodelay(stdscr, TRUE);
	noecho();
	cbreak();
	ScoreIt();

#ifdef ACS_VLINE
    /* good, we can use the defined forms-drawing characters */
    VERT = ACS_VLINE;
    HORIZ = ACS_HLINE;
    ULC = ACS_ULCORNER;
    URC = ACS_URCORNER;
    LLC = ACS_LLCORNER;
    LRC = ACS_LRCORNER;
#endif /* ACS_VLINE */

#ifdef A_COLOR
        init_colors();
#endif /* A_COLOR */
	/* initialize board to spaces */
	for (x=0; x<BOARD_WIDE; x++) 
		for (y=0; y<BOARD_HIGH; y++) 
			PUTCH(MINX+x,MINY+y,NO_CHAR);
	erase();
	DrawMenu();
	refresh();
}

/**************************************************************/
NewGame(void)
{
	register int x,y;

	CurrentPause=0;

	while (!CurrentPause) {
		GetKey();
		switch (Key) {
			case BEEP_KEY   : Beep = !Beep ;
					  if (Beep) beep(); 
					  break;
			case SCORE_KEY  : DrawScore(-1); break;
			case MENU_KEY	: DrawMenu(); break;
			case BOSS_KEY	: Boss(); break;
			case PLAY_KEY	: CurrentPause=InitPause; break;
			case QUIT_KEY   : Leave();
			}
	}
	/* initilialize board to spaces */
	for (x=0; x<BOARD_WIDE; x++) 
		for (y=0; y<BOARD_HIGH; y++) 
			PUTCH(MINX+x,MINY+y,NO_CHAR);
	ThisScore=0;
	mvaddstr(1,46, "000000");
	UPSCORE(0);

}

/******************************************************************/
DrawBox(int t, int l, int d, int w)
{
    register int x, y;

    for (y = t + 1; y < t + d; y++)
    {
	mvaddch(y, l, VERT);
	mvaddch(y, l + w, VERT);
    }
    for (x = l + 1; x < l + w; x++)
    {
	mvaddch(t, x, HORIZ);
	mvaddch(t + d, x, HORIZ);
    }
    mvaddch(t,         l,     ULC);
    mvaddch(t + d,     l,     LLC);
    mvaddch(t,         l + w, URC);
    mvaddch(t + d,     l + w, LRC);
}

/******************************************************************/
DrawMenu(void)
{
	register int y;
	erase(); 

	/* draw score border */
	DrawBox(0, 42, 2, 10);
	UPSCORE(0);

	/* draw menu */
        DrawBox(4, 35, 17, 28);
	mvaddstr( 6,36,"      ..   Menu   ..       ");
	mvaddstr( 7,36,"                           ");
	mvaddstr( 8,36,"   h     .... high scores  ");
	mvaddstr( 9,36,"   b     .... toggle beep  ");
	mvaddstr(10,36,"   p     .... play         ");
	mvaddstr(11,36,"   q     .... quit         ");
	mvaddstr(12,36,"                           ");
	mvaddstr(13,36," s or j  .... move left    ");
	mvaddstr(14,36," d or k  .... rotate piece ");
	mvaddstr(15,36," f or l  .... move right   ");
	mvaddstr(16,36,"  spc    .... fall piece   ");
	mvaddstr(17,36,"  esc    .... pause        ");
	mvaddstr(18,36,"                           ");
	mvaddstr(19,36,"                           ");
	mvaddstr(20,36,"                           ");

	/* draw game border */
	DrawBox(0, 14, 21, 11);

	DrawBox(NEXTROW, NEXTCOL, NEXT_HIGH, NEXT_WIDE);
	mvaddstr(NEXTROW + NEXT_HIGH + 1, NEXTCOL + 1, "Next");

	/* display the title */
	mvaddstr(3,17,"TETRIX");
	refresh();
}

/**************************************************************/
Play(void)
{
    int Type;	/* Type specifies rotation, shape and color of blocks */
    int Row;	/* Row of pivot point of block */
    int Column;	/* Column of pivot point of block */
    int	Next;

    Type = RandomPiece();
    while ((Key != QUIT_KEY) && CheckPiece(Type, MINX+STARTCOL, MINY+STARTROW))
    {
	int	x, y, ntype;

	DrawPiece(Type, MINX+STARTCOL, MINY+STARTROW);
	Next = RandomPiece();
	for (x = NEXTCOL + 1; x < NEXTCOL + NEXT_WIDE; x++)
	    for (y = NEXTROW + 1; y < NEXTROW + NEXT_HIGH; y++)
		mvaddch(y, x, ' ');
	DrawPiece(Next, NEXTCOL + 2, NEXTROW + 1);
	refresh();
	FallingDown = 0;
	Row = STARTROW; Column = STARTCOL; /* all pieces start at same point */

	do {			/* do until we can't Advance the piece */
	    if (FallingDown)
		Pause = 0;
	    else
		Pause = CurrentPause;
	    while (Pause)
	    {
		/* do this until pause runs out */
		Pause--;
		switch (Key)
		{
		case BOSS_KEY:
		    Boss();
		    DrawPiece(Next, NEXTCOL + 2, NEXTROW + 1);
		    break;

		case QUIT_KEY:
		    CurrentPause = 0;
		case FALL_KEY:
#ifdef KEY_MIN
		case KEY_DOWN:
#endif /* KEY_MIN */
		    FallingDown = 1;
		    UPSCORE(20-Row);
		    Pause = 0;
		    break;

		case RIGHT_KEY:
		case L_RIGHT_KEY:
#ifdef KEY_MIN
		case KEY_RIGHT:
#endif /* KEY_MIN */
		    if (MoveRight(Type, MINX + Column, MINY + Row))
			Column += 1;
		    else if (Beep)
			beep();
		    break;

		case LEFT_KEY:
		case L_LEFT_KEY:
#ifdef KEY_MIN
		case KEY_LEFT:
#endif /* KEY_MIN */
		    if (MoveLeft(Type, MINX + Column, MINY + Row))
			Column -= 1;
		    else if (Beep)
			beep();
		    break;

		case ROTATE_KEY:
		case L_ROTATE_KEY:
#ifdef KEY_MIN
		case KEY_UP:
#endif /* KEY_MIN */
		    ntype = Rotate(Type, MINX + Column, MINY + Row);
		    if (Beep && ntype == Type)
			beep();
		    Type = ntype;
		    break;

		case NULL_KEY:
		    break;

		default:
		    if (Beep)
			beep();
		    break;
		}
		GetKey();
	    }
	} while
	    (AdvancePiece(Type, MINX + Column, MINY + Row) && ++Row);
	UPSCORE(5);
	TestRows();
	Type = Next;
    }
}

/*********************************************************************/
ScoreIt(void)
{
	register int  oldmask,fd,i,j;

	oldmask = umask(0);
	if ((fd=open(SCORE_FILE,O_CREAT|O_RDONLY,0666)) != -1) {
		read(fd,High,sizeof(High));
		close(fd);
	}
	else {
	for(i=0; i<HIGHCOUNT; i++)
		High[i].Score = 0;
	for(i=0; i<HIGHCOUNT; i++)
		strncpy(High[i].Name,"         ",NAMELEN);
	}
	umask(oldmask);

	for (i=0; i<HIGHCOUNT; i++)		/* place this guy */
		if (High[i].Score <= ThisScore) break;

	if (i < HIGHCOUNT )			/* insert this score */
	{
		HighsChanged = 1;
		for (j=9; j>i; j--)		/* move down others */
			if (High[j-1].Score)
			{
				High[j].Score = High[j-1].Score;
				strncpy(High[j].Name,High[j-1].Name,NAMELEN);
			}
		cuserid((char *) High[i].Name);
		High[i].Score = ThisScore;
	}

	if (HighsChanged)
	{
		if ((fd=open(SCORE_FILE,O_RDWR)) != -1) {
			write(fd,High,sizeof(High));
			close(fd);
		}
		else mvaddstr(22,0,"Couldn't open high score file.");
	}
	
	return(i < HIGHCOUNT ? i : -1);
}

/***********************************************************************/
DrawScore(int highindex)
{
	register int j;

	mvaddstr( 5,36,"     Hit 'm' for menu      ");
	mvaddstr( 6,36,"                           ");
	mvaddstr( 7,36,"        HIGH SCORES        ");
	
	for (j=0; j<HIGHCOUNT; j++)
	   if (High[j].Score == 0)
		mvaddstr(j+8, 36,
                       "                           ");
	   else
	   {
	      if (j == highindex)
		  standout();
	      mvprintw(j+8, 36, "%2d. %-10s %-6d      ",
		       j + 1, (char *)High[j].Name,High[j].Score);
	      if (j == highindex)
		  standend();
	   }
	refresh();

}

/*********************************************************************/
Boss(void)
{	register int x,y;

	clear();
	DrawMenu();
	/* restore board */
	for (x=0; x<BOARD_WIDE; x++) 
		for (y=0; y<BOARD_HIGH; y++) 
			PUTCH(MINX+x,MINY+y,Board[x][y]);
	refresh();

}

/*********************************************************************/
GetKey(void)
{
	int c;

	Key = NULL_KEY;
	top:
	if ((c = getch()) == ERR) 
		return;
	else Key = c;
	goto top;
}

/************************************************************************/
/* Could be a macro for speed but cpp runs out of tree space in CanMove */
IS_FREE(x,y)
int x,y;
{
    return(INBOARD(x, y) && Board[x-MINX][y-MINY] == NO_CHAR);
}

/*********************************************************************/
TestRows(void)
{	register int x,y,tempy,fullrow;
	int marked[BOARD_HIGH];

	for (y=0; y<BOARD_HIGH; y++) {
	    marked[y] = 0;
	    for (x=0; x<BOARD_WIDE; x++)
		Temp[x][y] = NO_CHAR;
	}

	/* main loop to traverse Board, looking for fullrows */
	/* as it looks, it copies non full ones over to Temp */
	tempy=BOARD_HIGH-1;
	for (y=BOARD_HIGH-1; y>=0; y--) {
	    fullrow = 1;
	    for (x=0; x<BOARD_WIDE; x++) /* check for any holes at all */
		if (IS_FREE(MINX+x,MINY+y)) { fullrow = 0; break; }
	    if (fullrow) {
		marked[y]++;
		CurrentPause -= PAUSE_DECREMENT;	/* speed up the game */
	    }
	    else    {
		for (x=0; x<BOARD_WIDE; x++)
		    Temp[x][tempy] = Board[x][y];
		tempy--;
	    }
	}

	/* flash the rows that will die */
	for (tempy=1; tempy<5; tempy++)
	    for (y=BOARD_HIGH-1; y>=0; y--) 
		if (marked[y]) {	
		    UPSCORE(30-y);
		    for (x=0; x<BOARD_WIDE; x++)	
			PUTCH(MINX+x,MINY+y,BRITE_CHAR);
		    refresh();
		    for (x=0; x<BOARD_WIDE; x++)	
			PUTCH(MINX+x,MINY+y,NO_CHAR);
		    refresh();
		}

	/* Move temp back to Board */
	for (y=BOARD_HIGH-1; y>=0; y--) {
	    for (x=0; x<BOARD_WIDE; x++)
		PUTCH(MINX+x,MINY+y,Temp[x][y]);
	    refresh();
	}
    }

/***********************************************************/
Leave(void)
{
	erase();
#ifdef CHATTY
	mvaddstr(22,48,"Tetrix says Bye\n");
	mvaddstr(23,0,"");
	refresh();
	sleep(1);
#endif /* CHATTY */
	endwin();
	exit(0);
}

/**************************************************MAIN*****/
main(argc, argv)
int argc;
char **argv;
{
    if (argc >= 2)
	InitPause = atoi(argv[1]);
    else
	InitPause = DEFAULT_INITPAUSE;
    Init();
    for ( ; ; ) {
	NewGame();
	Play();
	DrawScore(ScoreIt());
    }
}
