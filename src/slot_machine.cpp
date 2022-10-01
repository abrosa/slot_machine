/* Copyright 2022 <Alexander Abrosov> */

#include "../include/slot_machine.hpp"

#include <cstdlib>
#include <random>

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

// Random speed in range
// MIN_SPEED + 0..ACCELERATION pixels per frame
int speed;

// Random start symbol in range 0..SYMBOLS_COUNT
int symbol;

// Frame counter
int countedFrames;

// The window renderer
extern SDL_Renderer *gRenderer;

int main(int argc, char *args[]) {
  // Use c++ random number generation facilities
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution1(0, SYMBOLS_COUNT - 1);
  std::uniform_int_distribution<int> distribution2(0, ACCELERATION - 1);

  // Init application
  LApplication *Application = new LApplication();

  // Event handler
  SDL_Event event;

  // Load resources
  gButton.loadMedia();
  gBackground.loadMedia();
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    symbol = distribution1(generator);
    gDrums[i].loadMedia(i, symbol);
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
        if (ROTATION_TIME[i] > curr_time - start_rotation) {
          speed = distribution2(generator);
          gDrums[i].update(MIN_SPEED + speed);
        } else {
          gDrums[i].slow();
        }
        if (FULL_STOP < curr_time - start_rotation) {
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
