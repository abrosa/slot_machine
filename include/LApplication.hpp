/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LAPPLICATION_HPP_
#define INCLUDE_LAPPLICATION_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

// Application class
class LApplication {
 public:
  // Application constructor
  LApplication();

  // Application destructor
  ~LApplication();

 private:
  // The window we'll be rendering to
  SDL_Window *gWindow = NULL;
};

#endif  // INCLUDE_LAPPLICATION_HPP_
