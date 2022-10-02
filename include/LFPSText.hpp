/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LFPSTEXT_HPP_
#define INCLUDE_LFPSTEXT_HPP_

#include "C:/x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "C:/x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"
// #include "../include/LApplication.hpp"
#include "../include/LLayout.hpp"

// Class for FPS text
class LFPSText {
 public:
  // Init LFPSText
  LFPSText();

  // Render text
  void render(char *buffer);

 private:
  // Rectangle for FPS text
  SDL_Rect FPSRectangle;

  // Color for FPS text
  SDL_Color FPSTextColor;

  // FPS text surface
  SDL_Surface *FPSSurface;

  // Texture
  SDL_Texture *FPSTexture;

  // Used monospaced font
  TTF_Font *font;
};

#endif  // INCLUDE_LFPSTEXT_HPP_
