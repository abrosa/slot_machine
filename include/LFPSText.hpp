/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LFPSTEXT_HPP_
#define INCLUDE_LFPSTEXT_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../include/LApplication.hpp"
#include "../include/LLayout.hpp"

// Class for FPS text
class LFPSText {
 public:
  // Initializes internal variables
  LFPSText();

  // count FPS
  void get_ticks(int countedFrames, Uint64 countedTicks);

  // Load media
  void loadMedia();

  // Render text
  void render();

 private:
  // Rectangle for FPS text
  SDL_Rect FPSRectangle;

  // Color for FPS text
  SDL_Color FPSTextColor;
};

#endif  // INCLUDE_LFPSTEXT_HPP_
