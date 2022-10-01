/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LDRUMS_HPP_
#define INCLUDE_LDRUMS_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

// The number of drums
const int DRUMS_COUNT = 5;

// Drums constants
const int DRUM_X = 50;
const int DRUM_Y = 50;
const int DRUM_WIDTH = 85;
const int DRUM_HEIGHT = 240;

// Next drums shifted +100 X
const int DRUM_STEP = 100;

// Drum size to loop it
const int DRUM_SIZE = 720;

// The drums
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
  // Drums positions
  SDL_Rect drums[DRUMS_COUNT];

  // Drums windows
  SDL_Rect viewpoints[DRUMS_COUNT];
};

#endif  // INCLUDE_LDRUMS_HPP_
