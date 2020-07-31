.PHONY: linux-opengl linux-sdl windows-sdl 

linux-opengl:
	gcc -o bin/GLtest src/GLtest.c src/olc_Engine.c src/olc_EngineOpenGL.c -I./include -lm -lX11 -lGL -lpthread -lpng
	./bin/GLtest

linux-sdl:
	gcc -o bin/SDLtest src/SDLtest.c src/olc_Engine.c src/olc_EngineSDL.c -I./include -lm -lSDL2 -lSDL2_image
	./bin/SDLtest

windows-sdl:
	gcc -o bin/SDLtest.exe src/SDLtest.c src/olc_Engine.c src/olc_EngineSDL.c -I./include -lm -lSDL2 -lSDL2_image
	bin\SDLtest.exe

windows-opengl:
	gcc -o bin/GLtest.exe src/GLtest.c src/olc_Engine.c src/olc_EngineOpenGL.c -I./include -lm -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi
	./bin/GLtest.exe
