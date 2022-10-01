/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LBUTTON_HPP_
#define INCLUDE_LBUTTON_HPP_

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

// Button constants
const int BUTTON_X = 560;
const int BUTTON_Y = 480;
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 80;

// Number of button sprites
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
  SDL_Rect mPosition;

  // Button window
  SDL_Rect gSpriteClips;
};

#endif  // INCLUDE_LBUTTON_HPP_
