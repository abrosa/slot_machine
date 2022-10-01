/* Copyright 2022 <Alexander Abrosov> */

#include "../include/slot_machine.hpp"

#include <sstream>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"
#include "../include/LButton.hpp"
#include "../include/LTexture.hpp"
#include "../include/LTimer.hpp"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Globally used font
TTF_Font *gFont = NULL;

// Mouse button sprites
extern SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
extern LTexture gButtonSpriteSheetTexture;

// Buttons objects
extern LButton gButtons;

// Scene textures
LTexture gFPSTextTexture;

bool init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }

    // Create window
    gWindow = SDL_CreateWindow("slot_machine", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Create vsynced renderer for window
      gRenderer = SDL_CreateRenderer(
          gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        success = false;
      } else {
        // Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          success = false;
        }

        // Initialize SDL_ttf
        if (TTF_Init() == -1) {
          printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
                 TTF_GetError());
          success = false;
        }
      }
    }
  }

  return success;
}

bool loadMedia() {
  // Loading success flag
  bool success = true;
  // Load sprites
  if (!gButtonSpriteSheetTexture.loadFromFile("../resources/button.bmp")) {
    printf("Failed to load button sprite texture!\n");
    success = false;
  } else {
    // Set sprites
    for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
      gSpriteClips[i].x = 0;
      gSpriteClips[i].y = i * BUTTON_HEIGHT;
      gSpriteClips[i].w = BUTTON_WIDTH;
      gSpriteClips[i].h = BUTTON_HEIGHT;
    }
    // Set buttons in corners
    gButtons.setPosition(300, 300);
  }
  // Open the font
  gFont = TTF_OpenFont("../resources/FiraSans-Bold.ttf", 32);
  if (gFont == NULL) {
    printf("Failed to load font. SDL_ttf Error: %s\n", TTF_GetError());
    success = false;
  }
  // Return with or without success
  return success;
}

void close() {
  // Free loaded images
  gButtonSpriteSheetTexture.free();
  // Free loaded images
  gFPSTextTexture.free();
  // Free global font
  TTF_CloseFont(gFont);
  gFont = NULL;
  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  // Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

int main(int argc, char *args[]) {
  // Start up SDL and create window
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    // Load media
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      // Main loop flag
      int quit = 0;
      // Event handler
      SDL_Event event;
      // Set text color as black
      SDL_Color textColor = {0, 0, 0, 255};
      // The frames per second timer
      LTimer fpsTimer;
      // In memory text stream
      std::stringstream timeText;
      // Start counting frames per second
      int countedFrames = 0;
      fpsTimer.start();
      // Load image for background
      SDL_Surface *background = IMG_Load("../resources/bg.jpg");
      SDL_Texture *groundTexture =
          SDL_CreateTextureFromSurface(gRenderer, background);
      // Load image for drums
      SDL_Surface *image = IMG_Load("../resources/drum.png");
      SDL_Texture *drumTexture = SDL_CreateTextureFromSurface(gRenderer, image);
      // Drums
      SDL_Rect drum1 = {0, 40, 85, 240};
      SDL_Rect drum2 = {0, 40, 85, 240};
      SDL_Rect drum3 = {0, 40, 85, 240};
      SDL_Rect drum4 = {0, 40, 85, 240};
      SDL_Rect drum5 = {0, 40, 85, 240};
      // Windows
      SDL_Rect viewpoint1 = {50, 50, 85, 240};
      SDL_Rect viewpoint2 = {150, 50, 85, 240};
      SDL_Rect viewpoint3 = {250, 50, 85, 240};
      SDL_Rect viewpoint4 = {350, 50, 85, 240};
      SDL_Rect viewpoint5 = {450, 50, 85, 240};
      // While application is running
      while (!quit) {
        // Move drums
        drum1.y -= 10;
        if (drum1.y < 0) {
          drum1.y += 720;
        }
        drum2.y -= 9;
        if (drum2.y < 0) {
          drum2.y += 720;
        }
        drum3.y -= 8;
        if (drum3.y < 0) {
          drum3.y += 720;
        }
        drum4.y -= 7;
        if (drum4.y < 0) {
          drum4.y += 720;
        }
        drum5.y -= 6;
        if (drum5.y < 0) {
          drum5.y += 720;
        }
        // Handle events on queue
        while (SDL_PollEvent(&event) != 0) {
          // User requests quit
          if (event.type == SDL_QUIT) {
            quit = -1;
          }
          // Handle button events
          gButtons.handleEvent(&event);
        }
        // Calculate and correct fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
        if (avgFPS > 2000000) {
          avgFPS = 0;
        }
        // Set text to be rendered
        timeText.str("");
        timeText << "FPS: " << avgFPS;
        // Render text
        if (!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(),
                                                  textColor)) {
          printf("Unable to render FPS texture!\n");
        }
        // Clear screen
        SDL_RenderClear(gRenderer);
        // Render background
        SDL_RenderCopy(gRenderer, groundTexture, NULL, NULL);
        // Render five drums
        SDL_RenderCopy(gRenderer, drumTexture, &drum1, &viewpoint1);
        SDL_RenderCopy(gRenderer, drumTexture, &drum2, &viewpoint2);
        SDL_RenderCopy(gRenderer, drumTexture, &drum3, &viewpoint3);
        SDL_RenderCopy(gRenderer, drumTexture, &drum4, &viewpoint4);
        SDL_RenderCopy(gRenderer, drumTexture, &drum5, &viewpoint5);
        // Render FPS
        gFPSTextTexture.render(20, 420);
        // Render buttons
        gButtons.render();
        // Update screen
        SDL_RenderPresent(gRenderer);
        // Count Frames
        ++countedFrames;
      }
    }
  }
  // Free resources and close SDL
  close();
  // Exit with good return code
  return 0;
}
