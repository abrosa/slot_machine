/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LBACKGROUND_HPP_
#define INCLUDE_LBACKGROUND_HPP_

#include "C:/x86_64-w64-mingw32/include/SDL2/SDL.h"
// #include "../include/LApplication.hpp"

// LBackground class
class LBackground {
 public:
  // Init LBackground
  LBackground();

  // Render background
  void render();

 private:
  // Background surface
  SDL_Surface *backgroundSurface;

  // Background texture
  SDL_Texture *backgroundTexture;
};

#endif  // INCLUDE_LBACKGROUND_HPP_
