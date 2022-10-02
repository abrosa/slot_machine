/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LRotation.hpp"

#include <random>

#include "../include/LDrum.hpp"
#include "../include/LMain.hpp"

// Milliseconds since the SDL library initialized
Uint64 curr_rotation_time;

// Random speed in range
// MIN_SPEED + 0..ACCELERATION pixels per frame
int speed;

// Drums to rotate
extern LDrum drums[DRUMS_COUNT];

LRotation::LRotation() {}

LRotation::~LRotation() {}

bool LRotation::step(Uint64 time_of_start) {
  // Flag for rotation status
  // true - it goes on
  // false - it stopped
  bool rotation_status = true;

  // Use c++ random number generation facilities
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution2(0, ACCELERATION - 1);

  // Get current ticks
  curr_rotation_time = SDL_GetTicks64() - time_of_start;

  // Iterate through all drums
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    // If rotation time has not ended
    if (ROTATION_TIME[i] > curr_rotation_time) {
      // Get random acceleration
      speed = distribution2(generator);

      // Update current drum with this speed (pixel per frame)
      drums[i].update(MIN_SPEED + speed);
    } else {
      // Or start to slow down this drum
      drums[i].slow();
    }

    // If it's time to full stop
    if (FULL_STOP < curr_rotation_time) {
      rotation_status = false;
    }
  }
  return rotation_status;
}
