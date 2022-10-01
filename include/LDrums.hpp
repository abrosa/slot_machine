/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LDRUMS_HPP_
#define INCLUDE_LDRUMS_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../include/LApplication.hpp"

// Geometry constants

// The number of drums
const int DRUMS_COUNT = 5;

// Size of window
const int WINDOW_SIZE = 3;

// Size of symbol
const int SYMBOL_WIDTH = 128;
const int SYMBOL_HEIGHT = SYMBOL_WIDTH;

// Number of different symbols
const int SYMBOLS_COUNT = 9;

// Gap between two drums
const int GAP = MARGIN_X / 2;

// Drums constants
const int DRUM_X = MARGIN_X;
const int DRUM_Y = MARGIN_Y;
const int DRUM_WIDTH =
    (SCREEN_WIDTH - 2 * MARGIN_X - (DRUMS_COUNT - 1) * GAP) / DRUMS_COUNT;
const int DRUM_HEIGHT = DRUM_WIDTH * WINDOW_SIZE;

// Next drums shifted to
const int DRUM_STEP = GAP + DRUM_WIDTH;

// Drum size to loop it
const int DRUM_SIZE = SYMBOL_HEIGHT * SYMBOLS_COUNT;

// Full drum size is higher for 3 symbols
// to change view without junction
const int FULL_DRUM_SIZE = SYMBOL_HEIGHT * (SYMBOLS_COUNT + WINDOW_SIZE);

// The drums
class LDrums {
 public:
  // Initializes internal variables
  LDrums();

  // Update views
  void update(int speed);

  // Slowly move to the next exact position and stop
  void slow();

  // Render drums
  void render();

  // Load media
  void loadMedia(int i, int symbol);

 private:
  // Drums positions
  SDL_Rect drums;

  // Drums windows
  SDL_Rect viewpoints;
};

#endif  // INCLUDE_LDRUMS_HPP_
