/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LDRUM_HPP_
#define INCLUDE_LDRUM_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
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
  // Update views
  void update();

  // Slowly move to the next exact position and stop
  void slow();

  // Load media
  void loadMedia(int i);

  // Render drum
  void render();

 private:
  // Drum positions
  SDL_Rect drumPosition;

  // Drum itself
  SDL_Rect drumRect;

  // Drum surface
  SDL_Surface *drumSurface;

  // Drum texture
  SDL_Texture *drumTexture;
};

#endif  // INCLUDE_LDRUM_HPP_
