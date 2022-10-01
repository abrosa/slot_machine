/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LBUTTON_HPP_
#define INCLUDE_LBUTTON_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"

// Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite {
  BUTTON_SPRITE_MOUSE_OUT = 0,
  BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
  BUTTON_SPRITE_MOUSE_DOWN = 2,
  BUTTON_SPRITE_MOUSE_UP = 3,
  BUTTON_SPRITE_TOTAL = 4
};

// The mouse button
class LButton {
 public:
  // Initializes internal variables
  LButton();

  // Sets top left position
  void setPosition(int x, int y);

  // Handles mouse event
  void handleEvent(SDL_Event *e);

  // Shows button sprite
  void render();

 private:
  // Top left position
  SDL_Point mPosition;

  // Currently used global sprite
  LButtonSprite mCurrentSprite;
};

#endif  // INCLUDE_LBUTTON_HPP_
