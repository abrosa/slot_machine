/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LBUTTON_HPP_
#define INCLUDE_LBUTTON_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../include/LApplication.hpp"
#include "../include/LLayout.hpp"

// Button sprites constants
const int SPRITES_COUNT = 4;
// Full size of resource image
const int SPRITES_SIZE = SPRITES_COUNT * BUTTON_HEIGHT;

// The mouse button
class LButton {
 public:
  // Initializes internal variables
  LButton();

  // Handles mouse event
  bool handleEvent(SDL_Event *e);

  // Flash button
  void update();

  // Shows button sprite
  void render();

  // Load media
  void loadMedia();

 private:
  // Button position
  SDL_Rect buttonPosition;

  // Button itself
  SDL_Rect buttonRect;
};

#endif  // INCLUDE_LBUTTON_HPP_
