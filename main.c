#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_HEIGHT = 560;
const int SCREEN_WIDTH = 960;

int main(int argc, char *args[]) {

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Window *window = SDL_CreateWindow("Majora", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Renderer *ren = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == NULL) {
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Surface *screen = SDL_LoadBMP("LAND3.BMP");
  if (screen == NULL) {
    printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, screen);
  SDL_FreeSurface(screen);
  if (tex == NULL ){
    printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    exit(1);
  }

  for(int i =0; i <3; i++) {
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren,tex,NULL,NULL);
    SDL_RenderPresent(ren);
    SDL_Delay(1000);
  }

  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}