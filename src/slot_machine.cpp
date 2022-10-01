/* Copyright 2022 <Alexander Abrosov> */

#include "../include/slot_machine.hpp"

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../include/LApplication.hpp"
#include "../include/LBackground.hpp"
#include "../include/LButton.hpp"
#include "../include/LDrums.hpp"
#include "../include/LFPSText.hpp"

// Objects for application
LButton gButton;
LBackground gBackground;
LDrums gDrums[DRUMS_COUNT];
LFPSText gFPSText;

// Milliseconds since the SDL library initialized
Uint64 start_time, curr_time;

// The moment of starting rotation
Uint64 start_rotation;
// Rotation time = 4000 - 5000 ms = 4 - 5 seconds
Uint64 rotation_time[DRUMS_COUNT] = {4000, 4260, 4520, 4780, 5040};
Uint64 full_stop = 5300;

// Frame counter
int countedFrames;

// The window renderer
extern SDL_Renderer *gRenderer;

int main(int argc, char *args[]) {
  // Init application
  LApplication *Application = new LApplication();

  // Event handler
  SDL_Event event;

  // Load resources
  gButton.loadMedia();
  gBackground.loadMedia();
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    gDrums[i].loadMedia(i);
  }
  gFPSText.loadMedia();

  // Start counting frames per second
  countedFrames = 0;
  start_time = SDL_GetTicks64();

  // Main loop flags
  bool quit_requested = false;
  bool button_pressed = false;
  bool drums_stopped = false;

  // While application is running
  while (!quit_requested) {
    // Handle events on queue
    while (SDL_PollEvent(&event) != 0) {
      // User requests quit
      if (event.type == SDL_QUIT) {
        quit_requested = true;
      }
      if (!button_pressed) {
        // Handle button events
        button_pressed = gButton.handleEvent(&event);
        if (button_pressed) {
          start_rotation = SDL_GetTicks64();
        }
      }
    }

    if (button_pressed) {
      curr_time = SDL_GetTicks64();
      for (int i = 0; i < DRUMS_COUNT; ++i) {
        if (rotation_time[i] > curr_time - start_rotation) {
          gDrums[i].update();
        }
        if (full_stop < curr_time - start_rotation) {
          drums_stopped = true;
        }
      }
    }

    // reset button for next roll
    if (drums_stopped) {
      button_pressed = false;
      drums_stopped = false;
    }

    // Flash button
    gButton.update();

    // Clear screen
    SDL_RenderClear(gRenderer);

    // Render objects
    gBackground.render();
    gButton.render();

    // Render drums
    for (int i = 0; i < DRUMS_COUNT; ++i) {
      gDrums[i].render();
    }

    // Get ticks at the end of frame
    curr_time = SDL_GetTicks64();
    gFPSText.get_text(countedFrames, start_time, curr_time);
    gFPSText.render();

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
