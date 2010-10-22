#include <stdlib.h>
#include <curses.h>
#include "tet.h"
/*********************************************************************/
/* Switch on type of piece, find out if I can move down */
/* If so, then do it and return 1 else return 0 */
/*********************************************************************/
AdvancePiece(int type, int col, int row)
{
    switch (type) {
	/*  WHITE PIECES  */
    case W_TYPE	: 
	if (IS_FREE(col-1,row+1) && 
	    IS_FREE(col,row+2) &&
	    IS_FREE(col+1,row+1)) 
	{
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-1,row+1,W_CHAR);
	    PUTCH(col,row+2,W_CHAR);
	    PUTCH(col+1,row+1,W_CHAR);
	    goto out;
	}
	else goto badout;

    case W_TYPE-1 :
	if (IS_FREE(col,row+2) && 
	    IS_FREE(col+1,row+1))
	{
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col,row+2,W_CHAR);
	    PUTCH(col+1,row+1,W_CHAR);
	    goto out;
	}
	else goto badout;

    case W_TYPE-2 :  
	if (IS_FREE(col-1,row+1) && 	
	    IS_FREE(col,row+1) && 
	    IS_FREE(col+1,row+1))
	{
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-1,row+1,W_CHAR);
	    PUTCH(col,row+1,W_CHAR);
	    PUTCH(col+1,row+1,W_CHAR);
	    goto out;
	}
	else goto badout;

    case W_TYPE-3 :  
	if (IS_FREE(col-1,row+1) && 	
	    IS_FREE(col,row+2))
	{
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col-1,row+1,W_CHAR);
	    PUTCH(col,row+2,W_CHAR);
	    goto out;
	}
	else goto badout;


	/*  RED PIECES  */
    case R_TYPE   : 
	if (IS_FREE(col-1,row+2) && 
	    IS_FREE(col,row+1) &&
	    IS_FREE(col+1,row+1))
	{
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-1,row+2,R_CHAR);
	    PUTCH(col,row+1,R_CHAR);
	    PUTCH(col+1,row+1,R_CHAR);
	    goto out;
	}
	else goto badout;

    case R_TYPE-1 : 
	if (IS_FREE(col,row+2) && 
	    IS_FREE(col+1,row+2))
	{
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col,row+2,R_CHAR);
	    PUTCH(col+1,row+2,R_CHAR);
	    goto out;
	}
	else goto badout;

    case R_TYPE-2 : 
	if (IS_FREE(col-1,row+1) && 
	    IS_FREE(col,row+1) &&
	    IS_FREE(col+1,row+1))
	{
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row-1,NO_CHAR);
	    PUTCH(col-1,row+1,R_CHAR);
	    PUTCH(col,row+1,R_CHAR);
	    PUTCH(col+1,row+1,R_CHAR);
	    goto out;
	}
	else goto badout;

    case R_TYPE-3 : 
	if (IS_FREE(col-1,row) && 
	    IS_FREE(col,row+2))
	{
	    PUTCH(col-1,row-1,NO_CHAR);
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col-1,row,R_CHAR);
	    PUTCH(col,row+2,R_CHAR);
	    goto out;
	}
	else goto badout;


	/*  TAN PIECES  */
    case T_TYPE   :
    case T_TYPE-1 :
    case T_TYPE-2 :
    case T_TYPE-3 :
	if (IS_FREE(col,row+2) && 
	    IS_FREE(col+1,row+2))
	{
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col,row+2,T_CHAR);
	    PUTCH(col+1,row+2,T_CHAR);
	    goto out;
	}
	else goto badout;


	/*  YELLOW PIECES  */
    case Y_TYPE   :
    case Y_TYPE-2 :  
	if (IS_FREE(col-1,row+2) && 
	    IS_FREE(col,row+2) &&
	    IS_FREE(col+1,row+1))
	{
	    PUTCH(col-1,row+1,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-1,row+2,Y_CHAR);
	    PUTCH(col,row+2,Y_CHAR);
	    PUTCH(col+1,row+1,Y_CHAR);
	    goto out;
	}
	else goto badout;

    case Y_TYPE-1 :
    case Y_TYPE-3 : 
	if (IS_FREE(col,row+1) && 
	    IS_FREE(col+1,row+2))
	{
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col,row+1,Y_CHAR);
	    PUTCH(col+1,row+2,Y_CHAR);
	    goto out;
	}
	else goto badout;


	/*  GREEN PIECES  */
    case G_TYPE   :
    case G_TYPE-2 : 
	if (IS_FREE(col-1,row+1) && 
	    IS_FREE(col,row+2) &&
	    IS_FREE(col+1,row+2))
	{
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row+1,NO_CHAR);
	    PUTCH(col-1,row+1,G_CHAR);
	    PUTCH(col,row+2,G_CHAR);
	    PUTCH(col+1,row+2,G_CHAR);
	    goto out;
	}
	else goto badout;

    case G_TYPE-1 :
    case G_TYPE-3 : 
	if (IS_FREE(col-1,row+2) && 
	    IS_FREE(col,row+1))
	{
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col,row+1,G_CHAR);
	    PUTCH(col-1,row+2,G_CHAR);
	    goto out;
	}
	else goto badout;


	/*  BLUE PIECES  */
    case B_TYPE   : 
	if (IS_FREE(col-1,row+1) && 
	    IS_FREE(col,row+1) &&
	    IS_FREE(col+1,row+2))
	{
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-1,row+1,B_CHAR);
	    PUTCH(col,row+1,B_CHAR);
	    PUTCH(col+1,row+2,B_CHAR);
	    goto out;
	}
	else goto badout;

    case B_TYPE-1 : 
	if (IS_FREE(col,row+2) && 
	    IS_FREE(col+1,row))
	{
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col+1,row-1,NO_CHAR);
	    PUTCH(col,row+2,B_CHAR);
	    PUTCH(col+1,row,B_CHAR);
	    goto out;
	}
	else goto badout;

    case B_TYPE-2 : 
	if (IS_FREE(col-1,row+1) && 
	    IS_FREE(col,row+1) &&
	    IS_FREE(col+1,row+1))
	{
	    PUTCH(col-1,row-1,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col-1,row+1,B_CHAR);
	    PUTCH(col,row+1,B_CHAR);
	    PUTCH(col+1,row+1,B_CHAR);
	    goto out;
	}
	else goto badout;

    case B_TYPE-3 : 
	if (IS_FREE(col-1,row+2) && 
	    IS_FREE(col,row+2))
	{
	    PUTCH(col-1,row+1,NO_CHAR);
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col-1,row+2,B_CHAR);
	    PUTCH(col,row+2,B_CHAR);
	    goto out;
	}
	else goto badout;


	/*  VIOLET PIECES  */
    case V_TYPE   :
    case V_TYPE-2 : 
	if (IS_FREE(col-1,row+1) && 
	    IS_FREE(col,row+1) && 
	    IS_FREE(col+1,row+1) && 
	    IS_FREE(col+2,row+1))
	{
	    PUTCH(col-1,row,NO_CHAR);
	    PUTCH(col,row,NO_CHAR);
	    PUTCH(col+1,row,NO_CHAR);
	    PUTCH(col+2,row,NO_CHAR);
	    PUTCH(col-1,row+1,V_CHAR);
	    PUTCH(col,row+1,V_CHAR);
	    PUTCH(col+1,row+1,V_CHAR);
	    PUTCH(col+2,row+1,V_CHAR);
	    goto out;
	}
	else goto badout;

    case V_TYPE-1 :
    case V_TYPE-3 : 
	if (IS_FREE(col,row+3)) 
	{
	    PUTCH(col,row-1,NO_CHAR);
	    PUTCH(col,row+3,V_CHAR);
	    goto out;
	}
	else goto badout;

    default : 
	printf("Advance Piece: illegal piece type=%d!!\n",type); 
	exit(0);
    }
badout:
    return(FALSE);
out:
    refresh();
    return(TRUE);
}
