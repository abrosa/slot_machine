/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LDrums.hpp"

#include <cstdio>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../include/slot_machine.hpp"

// Application renderer
extern SDL_Renderer *gRenderer;

// Drums surface
SDL_Surface *gDrumsSurface;

// Drums texture
SDL_Texture *gDrumsTexture;

// Drums constructor
LDrums::LDrums() {}

// Rotate drums
void LDrums::update(int speed) {
  // Roll drum up (-y)
  drums.y -= speed;

  // If drum ended, move back to bottom
  if (drums.y < 0) {
    drums.y += DRUM_SIZE;
  }
}

// Rotate drums
void LDrums::slow() {
  // If the drum is close to place
  if (drums.y % SYMBOL_HEIGHT < SLOW_SPEED) {
    // Round it coordinate to set it on place
    drums.y = (drums.y / SYMBOL_HEIGHT) * SYMBOL_HEIGHT;
  } else {
    // Else continue slow motion
    drums.y -= SLOW_SPEED;
  }
}

// Load image for drums
void LDrums::loadMedia(int i, int symbol) {
  // Load resource
  gDrumsSurface = IMG_Load("../resources/drum.png");

  // If load was unsuccesful, print error message
  if (gDrumsSurface == NULL) {
    printf("Failed to load image. SDL_image Error: %s\n", SDL_GetError());
  }

  // Viewpoints are placed on Window in series
  viewpoints = {DRUM_STEP * i + DRUM_X, DRUM_Y, DRUM_WIDTH, DRUM_HEIGHT};

  // Drums are set to random symbol
  drums = {0, symbol * SYMBOL_HEIGHT, DRUM_WIDTH, DRUM_HEIGHT};

  // Create texture from surface
  gDrumsTexture = SDL_CreateTextureFromSurface(gRenderer, gDrumsSurface);
}

// Render five drums
void LDrums::render() {
  SDL_RenderCopy(gRenderer, gDrumsTexture, &drums, &viewpoints);
}
