/* Copyright 2022 <Alexander Abrosov> */

#include "../include/slot_machine.hpp"

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"
#include "../include/LApplication.hpp"
#include "../include/LBackground.hpp"
#include "../include/LButton.hpp"
#include "../include/LDrums.hpp"
#include "../include/LFPSText.hpp"
#include "../include/LTexture.hpp"
#include "../include/LTimer.hpp"

// Background image
LBackground gBackground;

// Start button
LButton gButtons;

// Rolling drums
LDrums gDrums;

// FPS text
LFPSText gFPSText;

// FPS timer
LTimer fpsTimer;

// Milliseconds since the SDL library initialized
uint32_t ticks;

// Frame counter
int countedFrames;

// The window renderer
extern SDL_Renderer *gRenderer;

int main(int argc, char *args[]) {
  // Init application
  LApplication *Application = new LApplication();

  // Event handler
  SDL_Event event;

  // Load image for button
  gButtons.loadMedia();

  // Load image for background
  gBackground.loadMedia();

  // Load image for drums
  gDrums.loadMedia();

  // Start counting frames per second
  countedFrames = 0;
  fpsTimer.start();

  // Main loop flags
  bool quit_requested = false;
  bool start_spin = false;

  // While application is running
  while (!quit_requested) {
    // Handle events on queue
    while (SDL_PollEvent(&event) != 0) {
      // User requests quit
      if (event.type == SDL_QUIT) {
        quit_requested = true;
      }
      if (!start_spin) {
        // Handle button events
        start_spin = gButtons.handleEvent(&event);
      }
    }

    if (start_spin) {
      // Move drums
      gDrums.update();
    }

    // Flash button
    gButtons.update();

    // Clear screen
    SDL_RenderClear(gRenderer);

    // Render background
    gBackground.render();

    // Render five drums
    gDrums.render();

    // Calculate and render FPS
    ticks = fpsTimer.getTicks();
    gFPSText.render(countedFrames, ticks);

    // Render buttons
    gButtons.render();

    // Update screen
    SDL_RenderPresent(gRenderer);

    // Count Frames
    ++countedFrames;
  }

  // Free resources and close SDL
  delete Application;

  // Exit with good return code
  return 0;
}
