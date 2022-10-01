/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_SLOT_MACHINE_HPP_
#define INCLUDE_SLOT_MACHINE_HPP_

#include "../include/LDrums.hpp"

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

int main(int argc, char *argv[]);

#endif  // INCLUDE_SLOT_MACHINE_HPP_
