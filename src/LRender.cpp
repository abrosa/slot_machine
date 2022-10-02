/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LRender.hpp"

#include "../include/LBackground.hpp"
#include "../include/LButton.hpp"
#include "../include/LDrum.hpp"
#include "../include/LFPSText.hpp"

// The window renderer
extern SDL_Renderer *gRenderer;

// Objects for application
extern LButton button;
extern LBackground background;
extern LFPSText FPSText;
extern LDrum drums[DRUMS_COUNT];

// Render objects
void LRender::render() {
  // Clear screen
  SDL_RenderClear(gRenderer);

  // Render background
  background.render();

  // Render drums
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    drums[i].render();
  }

  // Render FPS text
  FPSText.render();

  // Render button
  button.render();

  // Update screen
  SDL_RenderPresent(gRenderer);
}
