#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_HEIGHT = 1000;
const int SCREEN_WIDTH = 1000;
SDL_Window *gWindow;
SDL_Surface *gScreen;
SDL_Renderer *gRenderer;

int init() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  gWindow = SDL_CreateWindow("Majora", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (gWindow == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    return 1;
  }

  gRenderer = SDL_CreateRenderer(
      gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (gRenderer == NULL) {
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    return 1;
  }
  return 0;
}

int loadBMP() {
  gScreen = SDL_LoadBMP("BLK.BMP");
  if (gScreen == NULL) {
    printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
    return 1;
  }
  return 0;
}

int main(int argc, char *args[]) {
  if (init()) {
    exit(1);
  }

  if (loadBMP()) {
    exit(1);
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(gRenderer, gScreen);
  SDL_FreeSurface(gScreen);
  if (tex == NULL) {
    printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    exit(1);
  }

  int close = 0;

  while (!close) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          close = 1;
          break;
        case SDL_KEYDOWN:
          switch (e.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
              printf("up");
              break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
              printf("left");
              break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
              printf("down");
              break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
              printf("right");
              break;
          }
        default:
          break;
      }
    }
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, tex, NULL, NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(1000 / 60);
  }

  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  SDL_Quit();
  return 0;
}
