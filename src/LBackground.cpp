/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LBackground.hpp"

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"

extern SDL_Renderer *gRenderer;

SDL_Texture *gBackgroundTexture;

LBackground::LBackground() {}

void LBackground::loadMedia() {
  // Load image for drums
  SDL_Surface *image = IMG_Load("../resources/bg.jpg");
  gBackgroundTexture = SDL_CreateTextureFromSurface(gRenderer, image);
}

void LBackground::render() {
  // Render background
  SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
}
