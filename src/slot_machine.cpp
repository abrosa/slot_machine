/* Copyright 2022 <Alexander Abrosov> */

#include "../include/slot_machine.hpp"
#include "../include/LMain.hpp"

// Pointer to lmain
LMain *lmain;

// Pointer to button
extern LButton *button;

// Pointer to rotation
extern LRotation *rotation;

// Pointer to render
extern LRender *render;

// Main entry point
int main(int argc, char *args[]) {
  // Init lmain
  lmain = new LMain();

  // Main loop flags
  bool quit_requested = false;
  bool start_pressed = false;
  bool drums_rolling = false;

  // While application is running
  while (!quit_requested) {
    // Handle events on queue
    while (SDL_PollEvent(&event) != 0) {
      // User requests quit
      if (event.type == SDL_QUIT) {
        quit_requested = true;
      }
      if (!start_pressed) {
        // Handle button pressed
        start_pressed = button->handleEvent(&event);
        if (start_pressed) {
          start_rotation_time = SDL_GetTicks64();
          start_pressed = false;
          drums_rolling = true;
        }
      }
    }

    // Start rotation if button was pressed
    if (drums_rolling) {
      drums_rolling = rotation->step(start_rotation_time);
    }

    // Reset button for next roll
    if (!drums_rolling) {
      start_pressed = false;
    }

    // Render objects
    render->render();
  }

  // Free lmain
  delete lmain;

  // Exit with good return code
  return 0;
}
