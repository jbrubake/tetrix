# To install:
#
#  - unpack this in /usr/src or /usr/local/src or something - doesn't matter.
#  - do a 'make install' in the tetrix directory
#  - tetrix gets installed in /usr/local/bin
#  - this will create a high score file in /usr/tmp, so doing it again
#    later on will erase high scores for the machine.

# Don't forget to change the spec file when you bump the version number.
VERSION=2.1

CFLAGS=-O -DIBM
LFLAGS = -s
OBJS= MoveR.o MoveL.o DrawP.o AdvanceP.o Rotate.o Colors.o tet.o
INCS= tet.h

SOURCES = 

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

install: tetrix.6 uninstall
	cp tetrix /usr/bin
	cp tetrix.6 /usr/share/man/man6/tetrix.6

uninstall:
	rm -f /usr/bin/install /usr/share/man/man6/tetrix.6

clean:
	rm -f tetrix tetrix.6 tetrix-*.rpm tetrix-*.tar.gz *~

SOURCES = READ.ME COPYING tetrix.xml Makefile tet.h $(OBJS:.o=.c) tetrix.spec

tetrix-$(VERS).tar.gz: $(SOURCES) tetrix.6
	@ls $(SOURCES) tetrix.6 | sed s:^:tetrix-$(VERS)/: >MANIFEST
	@(cd ..; ln -s tetrix tetrix-$(VERS))
	(cd ..; tar -czvf tetrix/tetrix-$(VERS).tar.gz `cat tetrix/MANIFEST`)
	@(cd ..; rm tetrix-$(VERS))

dist: tetrix-$(VERS).tar.gz

RPMROOT=/usr/src/redhat
RPM = rpm
RPMFLAGS = -ba
rpm: dist
	cp tetrix-$(VERS).tar.gz $(RPMROOT)/SOURCES;
	cp tetrix.spec $(RPMROOT)/SPECS
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) tetrix.spec	
	cp $(RPMROOT)/RPMS/`arch|sed 's/i[4-9]86/i386/'`/tetrix-$(VERS)*.rpm .
	cp $(RPMROOT)/SRPMS/tetrix-$(VERS)*.src.rpm .
