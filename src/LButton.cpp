/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LButton.hpp"

#include <cstdio>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"

// Application renderer
extern SDL_Renderer *gRenderer;

// Button surface
SDL_Surface *gButtonSurface;

// Button texture
SDL_Texture *gButtonTexture;

// Set button position
LButton::LButton() {
  mPosition = {BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
  gSpriteClips = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
}

// Processing mouse key press
bool LButton::handleEvent(SDL_Event *e) {
  bool key_pressed;
  // If mouse event happened
  if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);
    // Check if mouse key was pressed or released on the button
    key_pressed = false;
    if (x > mPosition.x && x < mPosition.x + BUTTON_WIDTH && y > mPosition.y &&
        y < mPosition.y + BUTTON_HEIGHT) {
      key_pressed = true;
    }
  }
  return key_pressed;
}

// Flash button
void LButton::update() {
  // Move sprite up to the next
  gSpriteClips.y -= BUTTON_HEIGHT;

  // If it was the last one, move down to the end
  if (gSpriteClips.y < 0) {
    gSpriteClips.y += SPRITES_SIZE;
  }
}

// Load image for button
void LButton::loadMedia() {
  gButtonSurface = IMG_Load("../resources/button.png");
  if (gButtonSurface == NULL) {
    printf("Failed to load image. SDL_image Error: %s\n", SDL_GetError());
  }

  // Create texture from surface
  gButtonTexture = SDL_CreateTextureFromSurface(gRenderer, gButtonSurface);
}

// Render button
void LButton::render() {
  SDL_RenderCopy(gRenderer, gButtonTexture, &gSpriteClips, &mPosition);
}
