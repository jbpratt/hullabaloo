#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  int up;
  int down;
  int left;
  int right;
} App;

typedef struct {
  int x;
  int y;
  SDL_Texture *texture;
} Entity;

App app;
Entity police;

SDL_Texture *loadTexture(char *filename) {
  SDL_Texture *texture;
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "Loading: %s ...", filename);

  texture = IMG_LoadTexture(app.renderer, filename);

  return texture;
}

void drawTex(SDL_Texture *texture, int x, int y) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void initSDL(void) {
  int rendererFlags, windowFlags;

  rendererFlags = SDL_RENDERER_ACCELERATED;

  windowFlags = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  app.window = SDL_CreateWindow("Majora", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, windowFlags);

  if (!app.window) {
    printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT,
           SDL_GetError());
    exit(1);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

  if (!app.renderer) {
    printf("Failed to create renderer: %s\n", SDL_GetError());
    exit(1);
  }

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void handleKeyUp(SDL_KeyboardEvent *event) {
  if (event->repeat == 0) {
    if (event->keysym.scancode == SDL_SCANCODE_UP) {
      app.up = 0;
    }
    if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
      app.down = 0;
    }
    if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
      app.left = 0;
    }
    if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
      app.right = 0;
    }
  }
}

void handleKeyDown(SDL_KeyboardEvent *event) {
  if (event->repeat == 0) {
    if (event->keysym.scancode == SDL_SCANCODE_UP) {
      app.up = 1;
    }
    if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
      app.down = 1;
    }
    if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
      app.left = 1;
    }
    if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
      app.right = 1;
    }
  }
}

void cleanup(void) {
  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyWindow(app.window);
  SDL_Quit();
}

void createScene(void) {
  SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
  SDL_RenderClear(app.renderer);
}

void presentScene(void) { SDL_RenderPresent(app.renderer); }

void handleInput(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        exit(0);
        break;
      case SDL_KEYDOWN:
        handleKeyDown(&event.key);
        break;
      case SDL_KEYUP:
        handleKeyUp(&event.key);
        break;
      default:
        break;
    }
  }
}

int main(int argc, char *argv[]) {
  memset(&app, 0, sizeof(App));
  memset(&police, 0, sizeof(Entity));
  initSDL();

  police.x = 100;
  police.y = 100;
  police.texture = loadTexture("assets/police.png");
  atexit(cleanup);

  while (1) {
    createScene();
    handleInput();

    if (app.up) {
      police.y -= 4;
    }
    if (app.down) {
      police.y += 4;
    }
    if (app.left) {
      police.x -= 4;
    }
    if (app.right) {
      police.x += 4;
    }

    drawTex(police.texture, police.x, police.y);
    presentScene();
    SDL_Delay(16);
  }
  return 0;
}
