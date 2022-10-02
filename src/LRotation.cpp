/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LRotation.hpp"

// Pointer to drums
extern LDrum *drums[DRUMS_COUNT];

bool LRotation::step(Uint64 time_of_start) {
  // Flag for rotation status
  // true - it goes on
  // false - it stopped
  bool rotation_status = true;

  // Get current ticks
  curr_rotation_time = SDL_GetTicks64() - time_of_start;

  // Iterate through all drums
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    // If rotation time has not ended
    if (ROTATION_TIME[i] > curr_rotation_time) {
      // Update current drum
      drums[i]->update();
    } else {
      // Or start to slow down this drum
      drums[i]->slow();
    }

    // If it's time to full stop
    if (FULL_STOP < curr_rotation_time) {
      rotation_status = false;
    }
  }
  return rotation_status;
}
