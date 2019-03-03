CC = g++
CFLAGS  = -g -Wall

INCLUDES = -I../include -I../include/libtcod

LFLAGS = -L. -Wl,-rpath=.
LIBS = -ltcod

SRCS = $(wildcard ../src/*.cpp)
OBJS = $(SRCS:.cpp = .o)

MAIN = trisquad

.PHONY: depend clean

all: $(MAIN)
	@echo  Compile Finished

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
