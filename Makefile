#  - un'cpio' this in /usr/src or /usr/local/src or something - doesn't matter.
#  - do a 'make install' in the tetrix directory
#  - tetrix gets installed in /usr/local/bin
#  - this will create a high score file in /usr/tmp, so doing it again
#    later on will erase high scores for the machine.

CFLAGS=-g -DEGA
LFLAGS = # -s
OBJS= MoveR.o MoveL.o DrawP.o AdvanceP.o Rotate.o Colors.o tet.o
INCS= tet.h

tetrix: $(OBJS) $(INCS)
	cc $(LFLAGS) $(OBJS) -ldcurses -o tetrix

MoveR.o: MoveR.c tet.h
MoveL.o: MoveL.c tet.h
DrawP.o: DrawP.c tet.h
AdvanceP.o: AdvanceP.c tet.h
Rotate.o: Rotate.c tet.h
Colors.o: Colors.c tet.h
tet.o: tet.c tet.h

install: tetrix
	chmod 755 tetrix
	/bin/mv -f tetrix /usr/local/bin

shar:
	shar README Makefile tet.h $(OBJS:.o=.c)

clean:
	/bin/rm -rf tetrix core *.o
