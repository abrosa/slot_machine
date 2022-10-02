/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LFPSText.hpp"

#include <cstdio>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"

// The window renderer
extern SDL_Renderer *gRenderer;

// Used monospaced font
TTF_Font *Font;

// FPS text surface
SDL_Surface *FPSSurface;

// Texture
SDL_Texture *FPSTexture;

// Double FPS counter
double avgFPS;

// Buffer for number converted to string
char buffer[12];

// Set text rectangle
LFPSText::LFPSText() {
  FPSRectangle = {TEXT_X, TEXT_Y, TEXT_WIDTH, TEXT_HEIGHT};
  // Set black color
  FPSTextColor = {0, 0, 0, 255};
}

// Calculate FPS and convert to text
void LFPSText::get_ticks(int countedFrames, Uint64 countedTicks) {
  // To prevent division by zero
  if (countedTicks != 0) {
    // Calculate FPS
    avgFPS = 1000.0L * countedFrames / countedTicks;

    // Convert double to string
    snprintf(buffer, sizeof(buffer), "FPS: %6.3f", avgFPS);
  } else {
    // Default string
    snprintf(buffer, sizeof(buffer), "FPS: 60.000");
  }
}

// Open the font
void LFPSText::loadMedia() {
  Font = TTF_OpenFont("../resources/FiraMono-Bold.ttf", 48);
  if (Font == NULL) {
    printf("Failed to load font. SDL_ttf Error: %s\n", TTF_GetError());
  }
}

// Render FPS text
void LFPSText::render() {
  // Create surface from text buffer
  FPSSurface = TTF_RenderText_Solid(Font, buffer, FPSTextColor);

  // Create texture from surface
  FPSTexture = SDL_CreateTextureFromSurface(gRenderer, FPSSurface);

  // Render FPS text
  SDL_RenderCopy(gRenderer, FPSTexture, NULL, &FPSRectangle);
}
