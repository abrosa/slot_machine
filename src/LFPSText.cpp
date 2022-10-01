/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LFPSText.hpp"

#include <cstdio>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"

// The window renderer
extern SDL_Renderer *gRenderer;

// Used monospaced font
TTF_Font *gFont;

// FPS text surface
SDL_Surface *gFPSSurface;

// Texture
SDL_Texture *gFPSTexture;

// Buffer for converting double to string
char buffer[8];

// Set text rectangle
LFPSText::LFPSText() {
  FPSRectangle = {TEXT_X, TEXT_Y, TEXT_WIDTH, TEXT_HEIGHT};
  // Set black color
  FPSTextColor = {0, 0, 0, 255};
}

// Calculate FPS and convert to text
void LFPSText::get_text(int countedFrames, Uint64 ticks1, Uint64 ticks2) {
  double avgFPS = 1000.0L * countedFrames / (ticks2 - ticks1);

  // Convert double to string
  snprintf(buffer, sizeof(buffer), "%6.3f", avgFPS);
}

// Open the font
void LFPSText::loadMedia() {
  gFont = TTF_OpenFont("../resources/FiraMono-Bold.ttf", 48);
  if (gFont == NULL) {
    printf("Failed to load font. SDL_ttf Error: %s\n", TTF_GetError());
  }
}

// Render FPS text
void LFPSText::render() {
  // Create surface from text buffer
  gFPSSurface = TTF_RenderText_Solid(gFont, buffer, FPSTextColor);

  // Create texture from surface
  gFPSTexture = SDL_CreateTextureFromSurface(gRenderer, gFPSSurface);

  // Render FPS text
  SDL_RenderCopy(gRenderer, gFPSTexture, NULL, &FPSRectangle);
}
