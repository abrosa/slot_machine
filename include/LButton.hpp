/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LBUTTON_HPP_
#define INCLUDE_LBUTTON_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../include/LLayout.hpp"

// Button sprites constants
const int SPRITES_COUNT = 4;
// Full size of resource image
const int SPRITES_SIZE = SPRITES_COUNT * BUTTON_HEIGHT;

// Blinking constants
const int PERIOD = 32;
const int THRESHOLD = 8;

// LButton class
class LButton {
 public:
  // Initializes internal variables
  LButton();

  // Handles mouse event
  bool handleEvent(SDL_Event *e);

  // Load media
  void loadMedia();

  // Shows button sprite
  void render();

 private:
  // Button position
  SDL_Rect buttonPosition;

  // Button itself
  SDL_Rect buttonRect;

  // Button surface
  SDL_Surface *buttonSurface;

  // Button texture
  SDL_Texture *buttonTexture;

  // Counter to flash button not so fast
  int inhibitor;
};

#endif  // INCLUDE_LBUTTON_HPP_
