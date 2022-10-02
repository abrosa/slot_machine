/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LBackground.hpp"

#include <cstdio>

#include "C:/x86_64-w64-mingw32/include/SDL2/SDL_image.h"

// Global SDL_Renderer
extern SDL_Renderer *gRenderer;

// Pointer to background
extern LBackground *background;

// Load image for background
LBackground::LBackground() {
  backgroundSurface = IMG_Load("../resources/bg.jpg");
  if (backgroundSurface == NULL) {
    printf("Failed to load image. SDL_image Error: %s\n", SDL_GetError());
  }

  // Create texture from surface
  backgroundTexture =
      SDL_CreateTextureFromSurface(gRenderer, backgroundSurface);
}

// Render background
void LBackground::render() {
  SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
}
