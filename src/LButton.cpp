/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LButton.hpp"

#include <cstdio>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"

// The window renderer
extern SDL_Renderer *gRenderer;

// Button surface
SDL_Surface *buttonSurface;

// Button texture
SDL_Texture *buttonTexture;

// Counter to flash button not so fast
int inhibitor;

// Set button position
LButton::LButton() {
  buttonPosition = {BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
  buttonRect = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
}

// Processing mouse key press
bool LButton::handleEvent(SDL_Event *e) {
  bool key_pressed;
  // If mouse event happened
  if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
    // Get mouse position
    SDL_Point mouse_position;
    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    // Check if mouse key was pressed or released on the button
    key_pressed = false;
    if (SDL_PointInRect(&mouse_position, &buttonPosition)) {
      key_pressed = true;
    }
  }
  return key_pressed;
}

// Flash button
void LButton::update() {
  --inhibitor;
  if (inhibitor < 0) {
    inhibitor += 64;
  }
  if (inhibitor < 8) {
    // Move sprite up to the next
    buttonRect.y -= BUTTON_HEIGHT;

    // If it was the last one, move down to the end
    if (buttonRect.y < 0) {
      buttonRect.y += SPRITES_SIZE;
    }
  }
}

// Load image for button
void LButton::loadMedia() {
  buttonSurface = IMG_Load("../resources/button.png");
  if (buttonSurface == NULL) {
    printf("Failed to load image. SDL_image Error: %s\n", SDL_GetError());
  }

  // Create texture from surface
  buttonTexture = SDL_CreateTextureFromSurface(gRenderer, buttonSurface);
}

// Render button
void LButton::render() {
  SDL_RenderCopy(gRenderer, buttonTexture, &buttonRect, &buttonPosition);
}
