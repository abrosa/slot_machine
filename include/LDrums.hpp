/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LDRUMS_HPP_
#define INCLUDE_LDRUMS_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

// The number of drums
const int DRUMS_COUNT = 5;

// The mouse button
class LDrums {
 public:
  // Initializes internal variables
  LDrums();

  // Update views
  void update();

  // Render drums
  void render();

  // Load media
  void loadMedia();

 private:
  // Drums
  SDL_Rect drums[DRUMS_COUNT];
  // Windows
  SDL_Rect viewpoints[DRUMS_COUNT];
};

#endif  // INCLUDE_LDRUMS_HPP_
