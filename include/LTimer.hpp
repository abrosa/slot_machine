/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LTIMER_HPP_
#define INCLUDE_LTIMER_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

// LTimer class
class LTimer {
 public:
  // LTimer start
  LTimer();

  // LTimer tick
  char *tick();

 private:
  // Milliseconds since the SDL library initialized
  Uint64 start_time;

  // Frame counter
  int countedFrames;

  // Ticks counter
  Uint64 countedTicks;

  // Double FPS counter
  double avgFPS;

  // Buffer for number converted to string
  char buffer[12];
};

#endif  // INCLUDE_LTIMER_HPP_
