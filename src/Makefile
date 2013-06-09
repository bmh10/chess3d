# Make file for Chess 3D #

CC      = c++
LD      = c++
CFLAGS  = -I/usr/X11R6/include -I. -c
LDFLAGS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXt -lXext -lX11 -lSM -lICE -lm # -lXi -lXmu

INCS = headers.h

OBJS = logger.o menuManager.o piece.o board.o game.o chess.o

COMPILE = $(CC) $(CFLAGS) $< -o $@

all: chess

chess: $(OBJS)
	$(LD) $(OBJS) -o chess $(LDFLAGS)

chess.o: chess.cpp $(INCS) ; $(COMPILE)

board.o: board.cpp board.h $(INCS); $(COMPILE)

game.o: game.cpp game.h $(INCS); $(COMPILE)

logger.o: logger.cpp logger.h $(INCS); $(COMPILE)

menuManager.o: menuManager.cpp menuManager.h $(INCS); $(COMPILE)

piece.o: piece.cpp piece.h $(INCS); $(COMPILE)

clean:
	rm -rf $(OBJS) chess



