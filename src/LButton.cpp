/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LButton.hpp"

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"
#include "../include/LTexture.hpp"
#include "../include/slot_machine.hpp"

LTexture gButtonSpriteSheetTexture;

// Mouse button sprites
SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];

LButton::LButton() {
  mPosition.x = 300;
  mPosition.y = 300;

  mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

// void LButton::setPosition(int x, int y) {
//   mPosition.x = x;
//   mPosition.y = y;
// }

void LButton::handleEvent(SDL_Event *e) {
  // If mouse event happened
  if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN ||
      e->type == SDL_MOUSEBUTTONUP) {
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Check if mouse is in button
    bool inside = true;

    // Mouse is left of the button
    if (x < mPosition.x) {
      inside = false;
      // Mouse is right of the button
    } else if (x > mPosition.x + BUTTON_WIDTH) {
      inside = false;
      // Mouse above the button
    } else if (y < mPosition.y) {
      inside = false;
      // Mouse below the button
    } else if (y > mPosition.y + BUTTON_HEIGHT) {
      inside = false;
    }

    // Mouse is outside button
    if (!inside) {
      mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
      // Mouse is inside button
    } else {
      // Set mouse over sprite
      switch (e->type) {
        case SDL_MOUSEMOTION:
          mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
          break;

        case SDL_MOUSEBUTTONDOWN:
          mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
          break;

        case SDL_MOUSEBUTTONUP:
          mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
          break;
      }
    }
  }
}

void LButton::render() {
  // Show current button sprite
  gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y,
                                   &gSpriteClips[mCurrentSprite]);
}

bool LButton::loadMedia() {
  // Loading success flag
  bool status = true;
  // Load sprites
  if (!gButtonSpriteSheetTexture.loadFromFile("../resources/button.bmp")) {
    printf("Failed to load button sprite texture!\n");
    status = false;
  } else {
    // Set sprites
    for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
      gSpriteClips[i].x = 0;
      gSpriteClips[i].y = i * BUTTON_HEIGHT;
      gSpriteClips[i].w = BUTTON_WIDTH;
      gSpriteClips[i].h = BUTTON_HEIGHT;
    }
  }
  // Return with or without success
  return status;
}
