/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LMain.hpp"

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"

#include "../include/LButton.hpp"
#include "../include/LRender.hpp"
#include "../include/LRotation.hpp"
#include "../include/LTimer.hpp"

// Button for processing key press
extern LButton button;

// Drums rotation
LRotation rotation;

// Rendering objects
LRender render;

// The moment of starting rotation
Uint64 start_rotation_time;

// Event handler
SDL_Event event;

// Timer object
LTimer timer;

// Main entry point
int main(int argc, char *args[]) {
  // Init application
  LApplication *application = new LApplication();

  // Load resources
  LLayout layout;

  // Create timer
  LTimer *timer = new LTimer();

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

    // Render objects
    render.render();
  }

  // Free resources and close SDL
  delete application;

  // Exit with good return code
  return 0;
}
