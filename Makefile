ifeq ($(OS),Windows_NT)
	EXT		:= .exe
	LIBS	:= -lm -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi
else
	EXT		:=
	LIBS	:= -lm -lX11 -lGL -lpthread -lpng
endif

.PHONY: all example drawing sprites decals

all: example drawing sprites decals

example:
	gcc -ggdb3 -Og -o demos/bin/example$(EXT) demos/example.c $(LIBS)

drawing:
	gcc -ggdb3 -Og -o demos/bin/drawing$(EXT) demos/drawing.c $(LIBS)

sprites:
	gcc -ggdb3 -Og -o demos/bin/sprites$(EXT) demos/sprites.c $(LIBS)

decals:
	gcc -ggdb3 -Og -o demos/bin/decals$(EXT) demos/decals.c $(LIBS)

