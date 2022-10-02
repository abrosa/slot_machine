/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LTimer.hpp"

#include <cstdio>

LTimer::LTimer() {
  // Start counting frames
  countedFrames = 0;

  // Get ticks at the start
  start_time = SDL_GetTicks64();
}

char *LTimer::tick() {
  // Count Frames
  ++countedFrames;

  // Get ticks at the end of frame
  countedTicks = SDL_GetTicks64() - start_time;

  // To prevent division by zero
  if (countedTicks != 0) {
    // Calculate FPS
    avgFPS = 1000.0L * countedFrames / countedTicks;

    // Convert double to string
    snprintf(buffer, sizeof(buffer), "FPS: %6.3f", avgFPS);
  } else {
    // Default string
    snprintf(buffer, sizeof(buffer), "FPS: 60.000");
  }
  return buffer;
}
