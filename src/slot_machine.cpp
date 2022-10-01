/* Copyright 2022 <Alexander Abrosov> */

#include "../include/slot_machine.hpp"

#include <sstream>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"
#include "../include/LApplication.hpp"
#include "../include/LButton.hpp"
#include "../include/LDrums.hpp"
#include "../include/LTexture.hpp"
#include "../include/LTimer.hpp"

LTexture gFPSTextTexture;

LButton gButtons;

LDrums gDrums;

// The window renderer
extern SDL_Renderer *gRenderer;

int main(int argc, char *args[]) {
  // Init application
  LApplication *Application = new LApplication();

  // Main loop flag
  int quit = 0;
  // Event handler
  SDL_Event event;
  // Set text color as black
  SDL_Color textColor = {0, 0, 0, 255};
  // The frames per second timer
  LTimer fpsTimer;
  // In memory text stream
  std::stringstream timeText;
  // Start counting frames per second
  int countedFrames = 0;
  fpsTimer.start();
  // ???
  gButtons.loadMedia();
  // Load image for background
  SDL_Surface *background = IMG_Load("../resources/bg.jpg");
  SDL_Texture *groundTexture =
      SDL_CreateTextureFromSurface(gRenderer, background);
  // Load image for drums
  gDrums.loadMedia();

  // Set buttons to place
  gButtons.setPosition(300, 300);

  // While application is running
  while (!quit) {
    // Move drums
    gDrums.update();
    // Handle events on queue
    while (SDL_PollEvent(&event) != 0) {
      // User requests quit
      if (event.type == SDL_QUIT) {
        quit = -1;
      }
      // Handle button events
      gButtons.handleEvent(&event);
    }
    // Calculate and correct fps
    float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
    if (avgFPS > 2000000) {
      avgFPS = 0;
    }
    // Set text to be rendered
    timeText.str("");
    timeText << "FPS: " << avgFPS;
    // Render text
    if (!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(),
                                              textColor)) {
      printf("Unable to render FPS texture!\n");
    }
    // Clear screen
    SDL_RenderClear(gRenderer);
    // Render background
    SDL_RenderCopy(gRenderer, groundTexture, NULL, NULL);
    // Render five drums
    gDrums.render();
    // Render FPS
    gFPSTextTexture.render(20, 420);
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
