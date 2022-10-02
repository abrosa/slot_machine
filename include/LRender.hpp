/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LRENDER_HPP_
#define INCLUDE_LRENDER_HPP_

#include "../include/LApplication.hpp"
#include "../include/LBackground.hpp"
#include "../include/LButton.hpp"
#include "../include/LDrum.hpp"
#include "../include/LFPSText.hpp"
#include "../include/LTimer.hpp"

// LRender class
class LRender {
 public:
  // Render all objects
  void render();

 private:
  // Buffer for printing FPS
  char *buffer;
};

#endif  // INCLUDE_LRENDER_HPP_
