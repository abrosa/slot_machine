/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LLayout.hpp"

#include "../include/LBackground.hpp"
#include "../include/LButton.hpp"
#include "../include/LDrum.hpp"
#include "../include/LFPSText.hpp"

// Objects for application
extern LButton button;
LBackground background;
LFPSText FPSText;
LDrum drums[DRUMS_COUNT];

// Load resources
LLayout::LLayout() {
  button.loadMedia();
  background.loadMedia();
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    drums[i].loadMedia(i);
  }
  FPSText.loadMedia();
}

LLayout::~LLayout() {}
