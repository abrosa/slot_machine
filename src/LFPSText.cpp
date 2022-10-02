/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LFPSText.hpp"

#include <cstdio>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

// The window renderer
extern SDL_Renderer *gRenderer;

// Set text rectangle
LFPSText::LFPSText() {
  FPSRectangle = {TEXT_X, TEXT_Y, TEXT_WIDTH, TEXT_HEIGHT};
  // Set black color
  FPSTextColor = {0, 0, 0, 255};
}

// Open the font
void LFPSText::loadMedia() {
  font = TTF_OpenFont("../resources/FiraMono-Bold.ttf", 48);
  if (font == NULL) {
    printf("Failed to load font. SDL_ttf Error: %s\n", TTF_GetError());
  }
}

// Render FPS text
void LFPSText::render(char *buffer) {
  // Create surface from text buffer
  FPSSurface = TTF_RenderText_Solid(font, buffer, FPSTextColor);

  // Create texture from surface
  FPSTexture = SDL_CreateTextureFromSurface(gRenderer, FPSSurface);

  // Render FPS text
  SDL_RenderCopy(gRenderer, FPSTexture, NULL, &FPSRectangle);
}
