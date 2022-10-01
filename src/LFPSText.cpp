/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LFPSText.hpp"

#include <sstream>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"
#include "../include/LTexture.hpp"
#include "../include/LTimer.hpp"

// Texture for rendering FPS text
LTexture gFPSTextTexture;

// The window renderer
extern SDL_Renderer *gRenderer;

LFPSText::LFPSText() {
  // Set text color as black
  FPSTextColor = {0, 0, 0, 255};
}

void LFPSText::render(int countedFrames, uint32_t ticks) {
  // Calculate and correct fps
  float avgFPS = countedFrames / (ticks / 1000.f);
  if (avgFPS > 2000000) {
    avgFPS = 0;
  }
  // Set text to be rendered
  timeText.str("");
  timeText << "FPS: " << avgFPS;
  // Render text
  if (!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(),
                                            FPSTextColor)) {
    printf("Unable to render FPS texture!\n");
  }
  // Render FPS
  gFPSTextTexture.render(20, 420);
}
