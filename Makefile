# To install:
#
#  - unpack this in /usr/src or /usr/local/src or something - doesn't matter.
#  - do a 'make install' in the tetrix directory
#  - tetrix gets installed in /usr/local/bin
#  - this will create a high score file in /var/games, so doing it again
#    later on will erase high scores for the machine.

VERS=2.4

# Withoiut the last option, modern GCC throws a 'stack smashing detected'
# error on startup that seems to be spurious
CFLAGS=-O -DIBM -fno-stack-protector
LFLAGS = -s
OBJS= MoveR.o MoveL.o DrawP.o AdvanceP.o Rotate.o Colors.o tet.o
INCS= tet.h

tetrix: $(OBJS) $(INCS)
	cc $(LFLAGS) $(OBJS) -lncurses -o tetrix

MoveR.o: MoveR.c tet.h
MoveL.o: MoveL.c tet.h
DrawP.o: DrawP.c tet.h
AdvanceP.o: AdvanceP.c tet.h
Rotate.o: Rotate.c tet.h
Colors.o: Colors.c tet.h
tet.o: tet.c tet.h

tetrix.6: tetrix.xml
	xmlto man tetrix.xml

tetrix.html: tetrix.xml
	xmlto html-nochunks tetrix.xml

install: tetrix.6 uninstall
	cp tetrix /usr/local/games
	cp tetrix.6 /usr/local/share/man/man6/tetrix.6

uninstall:
	rm -f /usr/local/games/tetrix
	rm -f /usr/local/share/man/man6/tetrix.6

clean:
	rm -f tetrix *.o tetrix tetrix.6 tetrix-*.rpm tetrix-*.tar.gz *~
	rm -f tetrix.html MANIFEST

CPPCHECKOPTS =
cppcheck:
	cppcheck $(CPPCHECKOPTS) tet.h $(OBJS:.o=.c)

SOURCES = README COPYING NEWS control tetrix.xml Makefile tet.h $(OBJS:.o=.c)

tetrix-$(VERS).tar.gz: $(SOURCES) tetrix.6
	@ls $(SOURCES) tetrix.6 | sed s:^:tetrix-$(VERS)/: >MANIFEST
	@(cd ..; ln -s tetrix tetrix-$(VERS))
	(cd ..; tar -czf tetrix/tetrix-$(VERS).tar.gz `cat tetrix/MANIFEST`)
	@(cd ..; rm tetrix-$(VERS))

dist: tetrix-$(VERS).tar.gz

release: tetrix-$(VERS).tar.gz tetrix.html
	shipper version=$(VERS) | sh -e -x

refresh: tetrix.html
	shipper -N -w version=$(VERS) | sh -e -x
