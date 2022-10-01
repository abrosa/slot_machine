/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LButton.hpp"

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"

// Application renderer
extern SDL_Renderer *gRenderer;

// Button texture
SDL_Texture *gButtonTexture;

LButton::LButton() {}

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

void LButton::update() {
  // Flash button
  gSpriteClips.y -= 80;
  if (gSpriteClips.y < 0) {
    gSpriteClips.y += 320;
  }
}

void LButton::loadMedia() {
  // Load sprites
  SDL_Surface *image = IMG_Load("../resources/button.png");
  gButtonTexture = SDL_CreateTextureFromSurface(gRenderer, image);
  // Button position
  mPosition = {BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
  gSpriteClips = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
}

void LButton::render() {
  // Render button
  SDL_RenderCopy(gRenderer, gButtonTexture, &gSpriteClips, &mPosition);
}
