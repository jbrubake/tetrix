#include <stdlib.h>
#include <curses.h>
#include "tet.h"
/*********************************************************************/
/* A new piece is created on the game board if possible */
/* returns 0 if unable to do it */
/*********************************************************************/

/* returns a random number in the set 4 8 16 20 24 or 28 */
RandomPiece(void)
{
    return ((int)(mrand48() % 4) + 4) * 4;
}

CheckPiece(type, col, row)
int	type, col, row;
{
    switch (type)
    {
    case W_TYPE :		/* checked  */
	return(IS_FREE(col-1,row) && IS_FREE(col,row) &&
	       IS_FREE(col+1,row) && IS_FREE(col,row+1));

    case R_TYPE :		/* checked */
	return (IS_FREE(col-1,row) && IS_FREE(col,row) &&
	    IS_FREE(col+1,row) && IS_FREE(col-1,row+1));

    case T_TYPE :		/* checked */
	return (IS_FREE(col,row) && IS_FREE(col,row+1) &&
	    IS_FREE(col+1,row) && IS_FREE(col+1,row+1));

    case Y_TYPE :		/* checked */
	return (IS_FREE(col-1,row+1) && IS_FREE(col,row+1) &&
	    IS_FREE(col,row) && IS_FREE(col+1,row));

    case G_TYPE :		/* checked */
	return (IS_FREE(col-1,row) && IS_FREE(col,row) &&
	    IS_FREE(col,row+1) && IS_FREE(col+1,row+1));

    case B_TYPE :		/* checked */
	return (IS_FREE(col-1,row) && IS_FREE(col,row) &&
	    IS_FREE(col+1,row) && IS_FREE(col+1,row+1));

    case V_TYPE :		/* checked */
	return (IS_FREE(col-1,row) && IS_FREE(col,row) &&
	    IS_FREE(col+1,row) && IS_FREE(col+2,row));

    default:
	printf("illegal piece type=%d!!\n",type);
	exit(0);
	/*NOTREACHED*/
    }
}

DrawPiece(int type, int col, int row)
{
    switch (type)
    {
    case W_TYPE :		/* checked  */
	PUTCH(col-1,row,W_CHAR);
	PUTCH(col,row,W_CHAR);
	PUTCH(col+1,row,W_CHAR);
	PUTCH(col,row+1,W_CHAR);
	break;

    case R_TYPE :		/* checked */
	PUTCH(col-1,row,R_CHAR);
	PUTCH(col,row,R_CHAR);
	PUTCH(col+1,row,R_CHAR);
	PUTCH(col-1,row+1,R_CHAR);
	break;

    case T_TYPE :		/* checked */
	PUTCH(col,row,T_CHAR);
	PUTCH(col,row+1,T_CHAR);
	PUTCH(col+1,row,T_CHAR);
	PUTCH(col+1,row+1,T_CHAR);
	break;

    case Y_TYPE :		/* checked */
	PUTCH(col-1,row+1,Y_CHAR);
	PUTCH(col,row+1,Y_CHAR);
	PUTCH(col,row,Y_CHAR);
	PUTCH(col+1,row,Y_CHAR);
	break;

    case G_TYPE :		/* checked */
	PUTCH(col-1,row,G_CHAR);
	PUTCH(col,row,G_CHAR);
	PUTCH(col,row+1,G_CHAR);
	PUTCH(col+1,row+1,G_CHAR);
	break;

    case B_TYPE :		/* checked */
	PUTCH(col-1,row,B_CHAR);
	PUTCH(col,row,B_CHAR);
	PUTCH(col+1,row,B_CHAR);
	PUTCH(col+1,row+1,B_CHAR);
	break;

    case V_TYPE :		/* checked */
	PUTCH(col-1,row,V_CHAR);
	PUTCH(col,row,V_CHAR);
	PUTCH(col+1,row,V_CHAR);
	PUTCH(col+2,row,V_CHAR);
	break;

    default:
	printf("illegal piece type=%d!!\n",type);
	exit(0);
    }
    refresh();
}


