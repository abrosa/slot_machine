/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LMAIN_HPP_
#define INCLUDE_LMAIN_HPP_

#include "C:/x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../include/LApplication.hpp"
#include "../include/LLayout.hpp"
#include "../include/LRender.hpp"
#include "../include/LRotation.hpp"
#include "../include/LTimer.hpp"

// LMain class
class LMain {
 public:
  // LMain constructor
  LMain();

  // LMain destructor
  ~LMain();

 private:
  // Pointer to application
  LApplication *application;

  // Pointer to layout
  LLayout *layout;
};

#endif  // INCLUDE_LMAIN_HPP_
