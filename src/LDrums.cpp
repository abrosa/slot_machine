/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LDrums.hpp"

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"

// Application renderer
extern SDL_Renderer *gRenderer;

// Drums texture
SDL_Texture *gDrumsTexture;

LDrums::LDrums() {}

void LDrums::update() {
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    drums[i].y -= 20 - 2 * i;
    if (drums[i].y < 0) {
      drums[i].y += 720;
    }
  }
}

void LDrums::loadMedia() {
  // Load image for drums
  SDL_Surface *image = IMG_Load("../resources/drum.png");
  gDrumsTexture = SDL_CreateTextureFromSurface(gRenderer, image);
  // Drums positions
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    drums[i] = {0, 40, 85, 240};
  }
  // Drums windows
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    viewpoints[i] = {100 * i + 50, 50, 85, 240};
  }
}

void LDrums::render() {
  // Render five drums
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    SDL_RenderCopy(gRenderer, gDrumsTexture, &drums[i], &viewpoints[i]);
  }
}
