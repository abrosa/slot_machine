/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LDrum.hpp"

#include <cstdio>
#include <random>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../include/LRotation.hpp"

// The window renderer
extern SDL_Renderer *gRenderer;

// Drum surface
SDL_Surface *drumSurface;

// Drum texture
SDL_Texture *drumTexture;

// Rotate drum
void LDrum::update(int speed) {
  // Roll drum up (-y)
  drumRect.y -= speed;

  // If drum ended, move back to bottom
  if (drumRect.y < 0) {
    drumRect.y += SYMBOLS_SIZE;
  }
}

// Scroll drum
void LDrum::slow() {
  // If the drum is close to place
  if (drumRect.y % SYMBOL_HEIGHT < SLOW_SPEED) {
    // Round it coordinate to set it on place
    drumRect.y = (drumRect.y / SYMBOL_HEIGHT) * SYMBOL_HEIGHT;
  } else {
    // Else continue slow motion
    drumRect.y -= SLOW_SPEED;
  }
}

// Load image for drum
void LDrum::loadMedia(int i) {
  // Use c++ random number generation facilities
  std::uniform_real_distribution<double> distribution(1.0L, 2.0L);
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_int_distribution<int> symbol(0, SYMBOLS_COUNT - 1);

  // Load resource
  drumSurface = IMG_Load("../resources/drum.png");

  // If load was unsuccesful, print error message
  if (drumSurface == NULL) {
    printf("Failed to load image. SDL_image Error: %s\n", SDL_GetError());
  }

  // drumPositions are placed on Window in series
  drumPosition = {DRUM_X + DRUM_STEP * i, DRUM_Y, DRUM_WIDTH, DRUM_HEIGHT};

  // Different drums are set to random symbol
  drumRect = {0, symbol(generator) * SYMBOL_HEIGHT, SYMBOL_WIDTH,
              SYMBOL_HEIGHT * WINDOW_SIZE};

  // Create texture from surface
  drumTexture = SDL_CreateTextureFromSurface(gRenderer, drumSurface);
}

// Render drum
void LDrum::render() {
  SDL_RenderCopy(gRenderer, drumTexture, &drumRect, &drumPosition);
}
