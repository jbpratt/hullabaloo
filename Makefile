main: 
	gcc main.c `sdl2-config --cflags --libs`

clean:
	rm a.out
