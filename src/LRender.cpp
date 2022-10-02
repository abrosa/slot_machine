/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LRender.hpp"

// Global SDL_Renderer
extern SDL_Renderer *gRenderer;

// Pointer to background
extern LBackground *background;

// Pointer to button
extern LButton *button;

// Pointer to drums
extern LDrum *drums[DRUMS_COUNT];

// Pointer to timer
extern LTimer *timer;

// Pointer to FPSText
extern LFPSText *FPSText;

// Render objects
void LRender::render() {
  // Clear screen
  SDL_RenderClear(gRenderer);

  // Render background
  background->render();

  // Render drums
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    drums[i]->render();
  }

  // Get and render FPS text
  buffer = timer->tick();
  FPSText->render(buffer);

  // Render button
  button->render();

  // Update screen
  SDL_RenderPresent(gRenderer);
}
