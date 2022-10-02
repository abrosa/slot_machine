/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LTIMER_HPP_
#define INCLUDE_LTIMER_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

// LTimer class
class LTimer {
 public:
  // LTimer constructor
  LTimer();

  // LTimer destructor
  ~LTimer();

  // LTimer start
  void start();

  // LTimer tick
  void tick();

 private:
  // Milliseconds since the SDL library initialized
  Uint64 start_time;

  // Frame counter
  int countedFrames;
};

#endif  // INCLUDE_LTIMER_HPP_
