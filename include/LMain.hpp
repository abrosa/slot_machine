/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LMAIN_HPP_
#define INCLUDE_LMAIN_HPP_

#include "../include/LDrum.hpp"
#include "../include/LLayout.hpp"

// LMain class
class LMain {
 public:
  // LMain constructor
  LMain();

  // LMain destructor
  ~LMain();

 private:
  // drums
  LDrum drums[DRUMS_COUNT];
};

#endif  // INCLUDE_LMAIN_HPP_
