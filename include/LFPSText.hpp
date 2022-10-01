/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LFPSTEXT_HPP_
#define INCLUDE_LFPSTEXT_HPP_

#include <sstream>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

// Class for FPS text
class LFPSText {
 public:
  // Initializes internal variables
  LFPSText();

  // Render text
  void render(int countedFrames, uint32_t ticks);

 private:
  // Color for FPS text
  SDL_Color FPSTextColor;

  // In memory text stream
  std::stringstream timeText;
};

#endif  // INCLUDE_LFPSTEXT_HPP_
