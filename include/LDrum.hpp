/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LDRUM_HPP_
#define INCLUDE_LDRUM_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../include/LApplication.hpp"
#include "../include/LLayout.hpp"

// Drum symbols constants
// Vertical window size
const int WINDOW_SIZE = 3;
// Number of different symbols
const int SYMBOLS_COUNT = 9;
// Size of symbol
const int SYMBOL_WIDTH = 128;
const int SYMBOL_HEIGHT = SYMBOL_WIDTH;
// Drum size to loop it
const int SYMBOLS_SIZE = SYMBOL_HEIGHT * SYMBOLS_COUNT;

// The drum
class LDrum {
 public:
  // Initializes internal variables
  LDrum();

  // Update views
  void update(int speed);

  // Slowly move to the next exact position and stop
  void slow();

  // Render drum
  void render();

  // Load media
  void loadMedia(int i, int symbol);

 private:
  // Drum positions
  SDL_Rect drumPosition;

  // Drum itself
  SDL_Rect drumRect;
};

#endif  // INCLUDE_LDRUM_HPP_
