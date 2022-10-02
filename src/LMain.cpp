/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LMain.hpp"

#include <cstdlib>
#include <random>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../include/LApplication.hpp"
#include "../include/LBackground.hpp"
#include "../include/LButton.hpp"
#include "../include/LDrum.hpp"
#include "../include/LFPSText.hpp"
#include "../include/LRotation.hpp"

// The window renderer
extern SDL_Renderer *gRenderer;

// Objects for application
LButton button;
LBackground background;
LFPSText FPSText;
LDrum drums[DRUMS_COUNT];
LRotation rotation;

// Milliseconds since the SDL library initialized
Uint64 start_time, countedTicks;

// The moment of starting rotation
Uint64 start_rotation_time;

// Random start symbol in range 0..SYMBOLS_COUNT
int symbol;

// Frame counter
int countedFrames;

LMain::LMain() {}

LMain::~LMain() {}

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
  button.loadMedia();
  background.loadMedia();
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    symbol = distribution1(generator);
    drums[i].loadMedia(i, symbol);
  }
  FPSText.loadMedia();

  // Start counting frames per second
  countedFrames = 0;
  start_time = SDL_GetTicks64();

  // Main loop flags
  bool quit_requested = false;
  bool button_pressed = false;
  bool rotation_status = true;

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
        button_pressed = button.handleEvent(&event);
        if (button_pressed) {
          start_rotation_time = SDL_GetTicks64();
        }
      }
    }

    if (button_pressed) {
      rotation_status = rotation.step(start_rotation_time);
    }

    // reset button for next roll
    if (!rotation_status) {
      button_pressed = false;
      rotation_status = true;
    }

    // Flash button
    button.update();

    // Clear screen
    SDL_RenderClear(gRenderer);

    // Render objects
    background.render();
    button.render();

    // Render drums
    for (int i = 0; i < DRUMS_COUNT; ++i) {
      drums[i].render();
    }

    // Get ticks at the end of frame
    countedTicks = SDL_GetTicks64() - start_time;
    FPSText.get_ticks(countedFrames, countedTicks);
    FPSText.render();

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
