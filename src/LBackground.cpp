/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LBackground.hpp"

#include <cstdio>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"

// The window renderer
extern SDL_Renderer *gRenderer;

// Background surface
SDL_Surface *gBackgroundSurface;

// Background texture
SDL_Texture *gBackgroundTexture;

// Empty constructor
LBackground::LBackground() {}

// Load image for background
void LBackground::loadMedia() {
  gBackgroundSurface = IMG_Load("../resources/bg.jpg");
  if (gBackgroundSurface == NULL) {
    printf("Failed to load image. SDL_image Error: %s\n", SDL_GetError());
  }

  // Create texture from surface
  gBackgroundTexture =
      SDL_CreateTextureFromSurface(gRenderer, gBackgroundSurface);
}

// Render background
void LBackground::render() {
  SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
}
