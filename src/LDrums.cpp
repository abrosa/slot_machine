/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LDrums.hpp"

#include <cstdio>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"

// Application renderer
extern SDL_Renderer *gRenderer;

// Drums surface
SDL_Surface *gDrumsSurface;

// Drums texture
SDL_Texture *gDrumsTexture;

// Drums constructor
LDrums::LDrums() { drums = {0, 0, DRUM_WIDTH, DRUM_HEIGHT}; }

// Rotate drums
void LDrums::update() {
  drums.y -= 80;
  if (drums.y < 0) {
    drums.y += DRUM_SIZE;
  }
}

// Load image for drums
void LDrums::loadMedia(int i) {
  gDrumsSurface = IMG_Load("../resources/drum.png");
  if (gDrumsSurface == NULL) {
    printf("Failed to load image. SDL_image Error: %s\n", SDL_GetError());
  }

  viewpoints = {DRUM_STEP * i + DRUM_X, DRUM_Y, DRUM_WIDTH, DRUM_HEIGHT};

  // Create texture from surface
  gDrumsTexture = SDL_CreateTextureFromSurface(gRenderer, gDrumsSurface);
}

// Render five drums
void LDrums::render() {
  SDL_RenderCopy(gRenderer, gDrumsTexture, &drums, &viewpoints);
}
