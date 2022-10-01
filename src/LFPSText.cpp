/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LFPSText.hpp"

#include <sstream>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"

// Texture for rendering FPS text
// LTexture gFPSTextTexture;

// The window renderer
extern SDL_Renderer *gRenderer;

// Globally used font
TTF_Font *gFont;

// Texture
SDL_Texture *gFPSTexture;

LFPSText::LFPSText() {
  // Set text rectangle
  FPSRectangle = {20, 420, 200, 80};
}

void LFPSText::get_text(int countedFrames, Uint64 ticks1, Uint64 ticks2) {
  // Calculate FPS
  double avgFPS = 1000.0L * countedFrames / (ticks2 - ticks1);
  // debug double avgFPS = 1.0L * (ticks2 - ticks1);

  // Convert double to string
  char buffer[8];
  snprintf(buffer, sizeof(buffer), "%6.3f", avgFPS);

  // Define color
  SDL_Color Black = {0, 0, 0, 255};

  // Render text surface
  SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, buffer, Black);
  // Create texture from surface
  gFPSTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
}

void LFPSText::loadMedia() {
  // Open the font
  gFont = TTF_OpenFont("../resources/FiraSans-Bold.ttf", 24);
  if (gFont == NULL) {
    printf("Failed to load font. SDL_ttf Error: %s\n", TTF_GetError());
  }
}

void LFPSText::render() {
  // Render button
  SDL_RenderCopy(gRenderer, gFPSTexture, NULL, &FPSRectangle);
}
