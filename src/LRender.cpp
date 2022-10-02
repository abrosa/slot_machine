/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LRender.hpp"

#include "../include/LBackground.hpp"
#include "../include/LButton.hpp"
#include "../include/LDrum.hpp"
#include "../include/LFPSText.hpp"
#include "../include/LTimer.hpp"

// Extern renderer
extern SDL_Renderer *gRenderer;

// Extern objects for rendering
extern LBackground background;
extern LDrum drums[DRUMS_COUNT];
extern LFPSText FPSText;
extern LButton button;

// Timer to get FPS
extern LTimer timer;

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

  // Get and render FPS text
  buffer = timer.tick();
  FPSText.render(buffer);

  // Render button
  button.render();

  // Update screen
  SDL_RenderPresent(gRenderer);
}
