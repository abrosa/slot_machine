/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LROTATION_HPP_
#define INCLUDE_LROTATION_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../include/LLayout.hpp"

// Rolling speed constants
// Minimal speed pixels per frame
const int MIN_SPEED = 32;

// Random acceleration (max speed - min speed)
const int ACCELERATION = 16;

// Slow speed to set symbols on place
const int SLOW_SPEED = 4;

// Timings constants
// Milliseconds for full stop rolling
const int FULL_STOP = 5600;

// Milliseconds for full stop every drum ~ 4-5 seconds
const int ROTATION_TIME[DRUMS_COUNT] = {4000, 4260, 4520, 4780, 5040};

// Rotation class
class LRotation {
 public:
  // Rotation constructor
  LRotation();

  // Rotation destructor
  ~LRotation();

  // Rotation step
  bool step(Uint64 time_of_start);
};

#endif  // INCLUDE_LROTATION_HPP_
