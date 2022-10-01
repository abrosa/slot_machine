/* Copyright 2022 <Alexander Abrosov> */

#include "../include/slot_machine.hpp"

#include <sstream>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"
#include "../include/LApplication.hpp"
#include "../include/LButton.hpp"
#include "../include/LTexture.hpp"
#include "../include/LTimer.hpp"

// SDL_Renderer *gRenderer = NULL;

LTexture gFPSTextTexture;

LButton gButtons;

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
  SDL_Surface *image = IMG_Load("../resources/drum.png");
  SDL_Texture *drumTexture = SDL_CreateTextureFromSurface(gRenderer, image);
  // Drums
  SDL_Rect drum1 = {0, 40, 85, 240};
  SDL_Rect drum2 = {0, 40, 85, 240};
  SDL_Rect drum3 = {0, 40, 85, 240};
  SDL_Rect drum4 = {0, 40, 85, 240};
  SDL_Rect drum5 = {0, 40, 85, 240};
  // Windows
  SDL_Rect viewpoint1 = {50, 50, 85, 240};
  SDL_Rect viewpoint2 = {150, 50, 85, 240};
  SDL_Rect viewpoint3 = {250, 50, 85, 240};
  SDL_Rect viewpoint4 = {350, 50, 85, 240};
  SDL_Rect viewpoint5 = {450, 50, 85, 240};

  // Set buttons to place
  gButtons.setPosition(300, 300);

  // While application is running
  while (!quit) {
    // Move drums
    drum1.y -= 10;
    if (drum1.y < 0) {
      drum1.y += 720;
    }
    drum2.y -= 9;
    if (drum2.y < 0) {
      drum2.y += 720;
    }
    drum3.y -= 8;
    if (drum3.y < 0) {
      drum3.y += 720;
    }
    drum4.y -= 7;
    if (drum4.y < 0) {
      drum4.y += 720;
    }
    drum5.y -= 6;
    if (drum5.y < 0) {
      drum5.y += 720;
    }
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
    SDL_RenderCopy(gRenderer, drumTexture, &drum1, &viewpoint1);
    SDL_RenderCopy(gRenderer, drumTexture, &drum2, &viewpoint2);
    SDL_RenderCopy(gRenderer, drumTexture, &drum3, &viewpoint3);
    SDL_RenderCopy(gRenderer, drumTexture, &drum4, &viewpoint4);
    SDL_RenderCopy(gRenderer, drumTexture, &drum5, &viewpoint5);
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
