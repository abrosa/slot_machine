/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LFPSText.hpp"

#include <cstdio>

#include "C:/x86_64-w64-mingw32/include/SDL2/SDL.h"

// Global SDL_Renderer
extern SDL_Renderer *gRenderer;

// Pointer to FPSText
extern LFPSText *FPSText;

// Init FPS text
LFPSText::LFPSText() {
  // Set text rectangle
  FPSRectangle = {TEXT_X, TEXT_Y, TEXT_WIDTH, TEXT_HEIGHT};
  // Set black color
  FPSTextColor = {0, 0, 0, 255};
  font = TTF_OpenFont("../resources/FiraMono-Bold.ttf", 48);
  if (font == NULL) {
    printf("Failed to load font. SDL_ttf Error: %s\n", TTF_GetError());
  }
}

// Render FPS text created dynamically
void LFPSText::render(char *buffer) {
  // Create surface from text buffer
  FPSSurface = TTF_RenderText_Solid(font, buffer, FPSTextColor);

  // Create texture from surface
  FPSTexture = SDL_CreateTextureFromSurface(gRenderer, FPSSurface);

  // Render FPS text
  SDL_RenderCopy(gRenderer, FPSTexture, NULL, &FPSRectangle);
}
