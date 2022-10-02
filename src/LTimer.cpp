/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LTimer.hpp"

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../include/LFPSText.hpp"

// FPSText object
LFPSText text;

LTimer::LTimer() {}

LTimer::~LTimer() {}

void LTimer::start() {
  // Start counting frames
  countedFrames = 0;

  // Get ticks at the start
  start_time = SDL_GetTicks64();
}

void LTimer::tick() {
  // Count Frames
  ++countedFrames;

  // Get ticks at the end of frame
  text.get_ticks(countedFrames, SDL_GetTicks64() - start_time);
}
