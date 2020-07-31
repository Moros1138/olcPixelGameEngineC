.PHONY: linux-sdl windows-sdl opengl

linux-sdl:
	gcc -o bin/SDLtest src/SDLtest.c src/olc_Engine.c src/olc_EngineSDL.c -I./include -lm -lSDL2 -lSDL2_image
	./bin/SDLtest

windows-sdl:
	gcc -o bin/SDLtest.exe src/SDLtest.c src/olc_Engine.c src/olc_EngineSDL.c -I./include -lm -lSDL2 -lSDL2_image
	bin\SDLtest.exe

opengl:
	gcc -o bin/GLtest src/GLtest.c src/engine.c -I./include -lm -lX11 -lGL -lpthread -lpng -ggdb3 -Og
