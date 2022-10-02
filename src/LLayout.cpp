/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LLayout.hpp"

#include "../include/LBackground.hpp"
#include "../include/LButton.hpp"
#include "../include/LDrum.hpp"
#include "../include/LFPSText.hpp"

// Background image
LBackground background;

// Array of drums
LDrum drums[DRUMS_COUNT];

//FPS text
LFPSText FPSText;

LButton button;

// Init layout
LLayout::LLayout() {
  // Load background image
  background.loadMedia();

  // Load drum image
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    drums[i].loadMedia(i);
  }

  // Load FPS text and render them
  FPSText.loadMedia();

  // Init button
  button.loadMedia();
}
