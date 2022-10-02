/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LAPPLICATION_HPP_
#define INCLUDE_LAPPLICATION_HPP_

#include "C:/x86_64-w64-mingw32/include/SDL2/SDL.h"

// LApplication class
class LApplication {
 public:
  // LApplication constructor
  LApplication();

  // LApplication destructor
  ~LApplication();

 private:
  // The window we'll be rendering to
  SDL_Window *gWindow;
};

#endif  // INCLUDE_LAPPLICATION_HPP_
