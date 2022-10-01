/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LFPSTEXT_HPP_
#define INCLUDE_LFPSTEXT_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

// Text position
const int TEXT_X = 40;
const int TEXT_Y = 502;

// Size of generated text exactly for this font
// "FPS: 60.000"
const int TEXT_WIDTH = 319;
const int TEXT_HEIGHT = 58;

// Class for FPS text
class LFPSText {
 public:
  // Initializes internal variables
  LFPSText();

  // Render text
  void get_text(int countedFrames, Uint64 ticks1, Uint64 ticks2);

  // Render text
  void render();

  // Load media
  void loadMedia();

 private:
  // Rectangle for FPS text
  SDL_Rect FPSRectangle;

  // Color for FPS text
  SDL_Color FPSTextColor;
};

#endif  // INCLUDE_LFPSTEXT_HPP_
