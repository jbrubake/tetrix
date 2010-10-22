#include <stdlib.h>
#include <curses.h>
#include "tet.h"
/*********************************************************************/
/* Switch on type of piece, find out if I can move left */
/* If so, then do it */
/*********************************************************************/
MoveLeft(int type, int col, int row)
{
    switch (type) {
	/*  WHITE PIECES  */
    case W_TYPE   :		/* checked */
	if (IS_FREE(col-2,row) && IS_FREE(col-1,row+1)) {
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col-2,row,W_CHAR);
	    PUTCH(col-1,row+1,W_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case W_TYPE-1 :		/* checked */
	if (IS_FREE(col-1,row-1) && IS_FREE(col-1,row) && 
	    IS_FREE(col-1,row+1)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col-1,row-1,W_CHAR);
	    PUTCH(col-1,row,W_CHAR);
	    PUTCH(col-1,row+1,W_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case W_TYPE-2 :		/* checked */
	if (IS_FREE(col-2,row) && IS_FREE(col-1,row-1)) {
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col-2,row,W_CHAR);
	    PUTCH(col-1,row-1,W_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case W_TYPE-3 :		/* checked */
	if (IS_FREE(col-1,row-1) && IS_FREE(col-2,row) && 
	    IS_FREE(col-1,row+1)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col-1,row-1,W_CHAR);
	    PUTCH(col-2,row,W_CHAR);
	    PUTCH(col-1,row+1,W_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;

	/*  RED PIECES  */
    case R_TYPE   :		/* checked */
	if (IS_FREE(col-2,row) && IS_FREE(col-2,row+1)) {
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-1,row+1,NO_CHAR);
	    PUTCH(col-2,row,R_CHAR);
	    PUTCH(col-2,row+1,R_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case R_TYPE-1 :		/* checked */
	if (IS_FREE(col-1,row-1) && IS_FREE(col-1,row) && 
	    IS_FREE(col-1,row+1)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col-1,row-1,R_CHAR);
	    PUTCH(col-1,row,R_CHAR);
	    PUTCH(col-1,row+1,R_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case R_TYPE-2 :		/* checked  */
	if (IS_FREE(col-2,row) && IS_FREE(col,row-1)) {
	    PUTCH(col+1,row-1,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-2,row,R_CHAR);
	    PUTCH(col,row-1,R_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case R_TYPE-3 :		/* checked */
	if (IS_FREE(col-2,row-1) && IS_FREE(col-1,row) && 
	    IS_FREE(col-1,row+1)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col-2,row-1,R_CHAR);
	    PUTCH(col-1,row,R_CHAR);
	    PUTCH(col-1,row+1,R_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;

	/*  TAN PIECES  */
    case T_TYPE   :
    case T_TYPE-1 :
    case T_TYPE-2 :
    case T_TYPE-3 :		/* checked */
	if (IS_FREE(col-1,row) && IS_FREE(col-1,row+1)) {
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col-1,row,T_CHAR);
	    PUTCH(col-1,row+1,T_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;

	/*  YELLOW PIECES  */
    case Y_TYPE   :
    case Y_TYPE-2 :		/* checked */
	if (IS_FREE(col-1,row) && IS_FREE(col-2,row+1)) {
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col-1,row,Y_CHAR);
	    PUTCH(col-2,row+1,Y_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case Y_TYPE-1 :
    case Y_TYPE-3 :		/* checked */
	if (IS_FREE(col-1,row-1) && IS_FREE(col-1,row) && 
	    IS_FREE(col,row+1)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col-1,row-1,Y_CHAR);
	    PUTCH(col-1,row,Y_CHAR);
	    PUTCH(col,row+1,Y_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;

	/*  GREEN PIECES  */
    case G_TYPE   :
    case G_TYPE-2 :		/* checked */
	if (IS_FREE(col-2,row) && IS_FREE(col-1,row+1)) {
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col-2,row,G_CHAR);
	    PUTCH(col-1,row+1,G_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case G_TYPE-1 :
    case G_TYPE-3 :		/* checked */
	if (IS_FREE(col-1,row-1) && IS_FREE(col-2,row) && 
	    IS_FREE(col-2,row+1)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col-1,row+1,NO_CHAR);
	    PUTCH(col-1,row-1,G_CHAR);
	    PUTCH(col-2,row,G_CHAR);
	    PUTCH(col-2,row+1,G_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;

	/*  BLUE PIECES  */
    case B_TYPE   :		/* checked */
	if (IS_FREE(col-2,row) && IS_FREE(col,row+1)) {
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col-2,row,B_CHAR);
	    PUTCH(col,row+1,B_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case B_TYPE-1 :		/* checked */
	if (IS_FREE(col-1,row-1) && IS_FREE(col-1,row) && 
	    IS_FREE(col-1,row+1)) {
	    PUTCH(col+1,row-1,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col-1,row-1,B_CHAR);
	    PUTCH(col-1,row,B_CHAR);
	    PUTCH(col-1,row+1,B_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case B_TYPE-2 :		/* checked */
	if (IS_FREE(col-2,row-1) && IS_FREE(col-2,row)) {
	    PUTCH(col-1,row-1,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-2,row-1,B_CHAR);
	    PUTCH(col-2,row,B_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case B_TYPE-3 :		/* checked */
	if (IS_FREE(col-1,row-1) && IS_FREE(col-1,row) && 
	    IS_FREE(col-2,row+1)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col-1,row-1,B_CHAR);
	    PUTCH(col-1,row,B_CHAR);
	    PUTCH(col-2,row+1,B_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;

	/*  VIOLET PIECES  */
    case V_TYPE   :
    case V_TYPE-2 :		/* checked */
	if (IS_FREE(col-2,row)) {
	    PUTCH(col+2,row,NO_CHAR);
	    PUTCH(col-2,row,V_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;
    case V_TYPE-1 :
    case V_TYPE-3 :		/* checked */
	if (IS_FREE(col-1,row-1) && IS_FREE(col-1,row) && 
	    IS_FREE(col-1,row+1) && IS_FREE(col-1,row+2)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col,row+2,NO_CHAR);
	    PUTCH(col-1,row-1,V_CHAR);
	    PUTCH(col-1,row,V_CHAR);
	    PUTCH(col-1,row+1,V_CHAR);
	    PUTCH(col-1,row+2,V_CHAR);
	    return(TRUE);
	}
	else
	    return(FALSE);
	break;

    default: 
	printf("illegal piece type=%d!!\n",type); 
	exit(0);
    }
}

