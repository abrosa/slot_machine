/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LMAIN_HPP_
#define INCLUDE_LMAIN_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

#include "../include/LRender.hpp"
#include "../include/LRotation.hpp"
#include "../include/LTimer.hpp"

// Drums rotation
LRotation rotation;

// Rendering objects
LRender render;

// The moment of starting rotation
Uint64 start_rotation_time;

// Event handler
SDL_Event event;

// Timer object
LTimer timer;

#endif  // INCLUDE_LMAIN_HPP_
