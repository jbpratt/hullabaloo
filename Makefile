main: 
	gcc src/main.c `sdl2-config --cflags --libs` -lSDL2_image -lm

clean:
	rm a.out
