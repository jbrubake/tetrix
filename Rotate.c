#include <stdlib.h>
#include <curses.h>
#include "tet.h"
/*********************************************************************/
/* Switch on type of piece, find out if I can rotate */
/* If so, then do it */
/*********************************************************************/
Rotate(int type, int col, int row)
{
    switch (type) {
	/*  WHITE PIECES  */
    case W_TYPE   :  /* checked */
	if (IS_FREE(col,row-1)) {
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col,row-1,W_CHAR);
	    type--;
	}
	break;
    case W_TYPE-1 :  /* checked */
	if (IS_FREE(col-1,row)) {
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col-1,row,W_CHAR);
	    type--;
	}
	break;
    case W_TYPE-2 :  /* checked */
	if (IS_FREE(col,row+1)) {
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col,row+1,W_CHAR);
	    type--;
	}
	break;
    case W_TYPE-3 :  /* checked */
	if (IS_FREE(col+1,row)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col+1,row,W_CHAR);
	    type = W_TYPE;
	}
	break;

	/*  RED PIECES  */
    case R_TYPE   : /* checked */
	if (IS_FREE(col,row-1) && IS_FREE(col,row+1) && 
	    IS_FREE(col+1,row+1)) {
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col-1,row+1,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col,row-1,R_CHAR);
	    PUTCH(col,row+1,R_CHAR);
	    PUTCH(col+1,row+1,R_CHAR);
	    type--;
	}
	break;
    case R_TYPE-1 : /* checked */
	if (IS_FREE(col-1,row) && IS_FREE(col+1,row-1) && 
	    IS_FREE(col+1,row)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col-1,row,R_CHAR);
	    PUTCH(col+1,row-1,R_CHAR);
	    PUTCH(col+1,row,R_CHAR);
	    type--;
	}
	break;
    case R_TYPE-2 : /* checked  */
	if (IS_FREE(col-1,row-1) && IS_FREE(col,row-1) && 
	    IS_FREE(col,row+1)) {
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col+1,row-1,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-1,row-1,R_CHAR);
	    PUTCH(col,row-1,R_CHAR);
	    PUTCH(col,row+1,R_CHAR);
	    type--;
	}
	break;
    case R_TYPE-3 : /* checked */
	if (IS_FREE(col-1,row) && IS_FREE(col-1,row+1) && 
	    IS_FREE(col+1,row)) {
	    PUTCH(col-1,row-1,NO_CHAR);
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col-1,row,R_CHAR);
	    PUTCH(col-1,row+1,R_CHAR);
	    PUTCH(col+1,row,R_CHAR);
	    type = R_TYPE;
	}
	break;

	/*  TAN PIECES  */
    case T_TYPE   :
    case T_TYPE-1 :
    case T_TYPE-2 :
    case T_TYPE-3 : break;

	/*  YELLOW PIECES  */
    case Y_TYPE   :
    case Y_TYPE-2 :  /* checked */
	if (IS_FREE(col,row-1) && IS_FREE(col+1,row+1)) {
	    PUTCH(col-1,row+1,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col,row-1,Y_CHAR);
	    PUTCH(col+1,row+1,Y_CHAR);
	    type--;
	}
	break;
    case Y_TYPE-1 :
    case Y_TYPE-3 : /* checked */
	if (IS_FREE(col-1,row+1) && IS_FREE(col,row+1)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col-1,row+1,Y_CHAR);
	    PUTCH(col,row+1,Y_CHAR);
	    type = Y_TYPE;
	}
	break;

	/*  GREEN PIECES  */
    case G_TYPE   :
    case G_TYPE-2 : /* checked */
	if (IS_FREE(col-1,row+1) && IS_FREE(col,row-1)) {
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col-1,row+1,G_CHAR);
	    PUTCH(col,row-1,G_CHAR);
	    type--;
	}
	break;
    case G_TYPE-1 :
    case G_TYPE-3 : /* checked */
	if (IS_FREE(col,row+1) && IS_FREE(col+1,row+1)) {
	    PUTCH(col-1,row+1,NO_CHAR);
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row+1,G_CHAR);
	    PUTCH(col+1,row+1,G_CHAR);
	    type = G_TYPE;
	}
	break;


	/*  BLUE PIECES  */
    case B_TYPE   : /* checked */
	if (IS_FREE(col,row-1) && IS_FREE(col,row+1) && 
	    IS_FREE(col+1,row-1)) {
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col,row-1,B_CHAR);
	    PUTCH(col,row+1,B_CHAR);
	    PUTCH(col+1,row-1,B_CHAR);
	    type--;
	}
	break;
    case B_TYPE-1 : /* checked */
	if (IS_FREE(col-1,row-1) && IS_FREE(col-1,row) && 
	    IS_FREE(col+1,row)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col+1,row-1,NO_CHAR);
	    PUTCH(col-1,row-1,B_CHAR);
	    PUTCH(col-1,row,B_CHAR);
	    PUTCH(col+1,row,B_CHAR);
	    type--;
	}
	break;
    case B_TYPE-2 : /* checked  */
	if (IS_FREE(col-1,row+1) && IS_FREE(col,row-1) && 
	    IS_FREE(col,row+1)) {
	    PUTCH(col-1,row-1,NO_CHAR);
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-1,row+1,B_CHAR);
	    PUTCH(col,row-1,B_CHAR);
	    PUTCH(col,row+1,B_CHAR);
	    type--;
	}
	break;
    case B_TYPE-3 : /* checked */
	if (IS_FREE(col-1,row) && IS_FREE(col+1,row) && 
	    IS_FREE(col+1,row+1)) {
	    PUTCH(col-1,row+1,NO_CHAR);
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col-1,row,B_CHAR);
	    PUTCH(col+1,row,B_CHAR);
	    PUTCH(col+1,row+1,B_CHAR);
	    type = B_TYPE;
	}
	break;

	/*  VIOLET PIECES  */
    case V_TYPE   :
    case V_TYPE-2 : /* checked */
	if (IS_FREE(col,row-1) && IS_FREE(col,row+1) && 
	    IS_FREE(col,row+2)) {
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col+2,row,NO_CHAR);
	    PUTCH(col,row-1,V_CHAR);
	    PUTCH(col,row+1,V_CHAR);
	    PUTCH(col,row+2,V_CHAR);
	    type--;
	}
	break;
    case V_TYPE-1 :
    case V_TYPE-3 : /* checked */
	if (IS_FREE(col-1,row) && IS_FREE(col+1,row) && 
	    IS_FREE(col+2,row)) {
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row+1,NO_CHAR);
	    PUTCH(col,row+2,NO_CHAR);
	    PUTCH(col-1,row,V_CHAR);
	    PUTCH(col,row,V_CHAR);
	    PUTCH(col+1,row,V_CHAR);
	    PUTCH(col+2,row,V_CHAR);
	    type = V_TYPE;
	}
	break;
    default : 
	printf("illegal piece type=%d!!\n",type); 
	exit(0);
    }
    refresh();
    return(type);
}

