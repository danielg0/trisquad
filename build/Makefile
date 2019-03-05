CC = g++
CCWIN = x86_64-w64-mingw32-g++
CFLAGS  = -g -Wall

INCLUDES = -I../include -I../include/libtcod

LFLAGS = -L. -Wl,-rpath=.
LIBS =  -ltcod -lSDL2

SRCS = $(wildcard ../src/*.cpp)
OBJS = $(SRCS:.cpp = .o)
FONT = terminal.png

MAIN = trisquad

.PHONY: depend clean

all: linux windows
	@echo  Compile Finished

dist: clean all
	mkdir linux
	cp $(MAIN) $(wildcard *.so*) $(FONT) linux
	mkdir windows
	cp $(MAIN).exe $(wildcard *.dll) $(FONT) windows

linux: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

windows: $(OBJS)
	$(CCWIN) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN) $(MAIN).exe
	$(RM) -r windows linux

depend: $(SRCS)
	makedepend $(INCLUDES) $^
