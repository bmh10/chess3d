# Make file for Chess 3D #

CC      = c++
LD      = c++
CFLAGS  = -I/usr/X11R6/include -I. -c
LDFLAGS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXt -lXext -lX11 -lSM -lICE -lm # -lXi -lXmu

INCS = headers.h

OBJS = logger.o box2d.o menuManager.o hud.o model.o modelManager.o piece.o board.o game.o chess.o

COMPILE = $(CC) $(CFLAGS) $< -o $@

all: chess

chess: $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS)

chess.o: chess.cpp $(INCS) ; $(COMPILE)

board.o: board.cpp board.h $(INCS); $(COMPILE)

game.o: game.cpp game.h $(INCS); $(COMPILE)

logger.o: logger.cpp logger.h $(INCS); $(COMPILE)

box2d.o: box2d.cpp box2d.h $(INCS); $(COMPILE)

menuManager.o: menuManager.cpp menuManager.h $(INCS); $(COMPILE)

hud.o: hud.cpp hud.h $(INCS); $(COMPILE)

model.o: model.cpp model.h $(INCS); $(COMPILE)

modelManager.o: modelManager.cpp modelManager.h $(INCS); $(COMPILE)

piece.o: piece.cpp piece.h $(INCS); $(COMPILE)

clean:
	rm -rf $(OBJS) chess *~



