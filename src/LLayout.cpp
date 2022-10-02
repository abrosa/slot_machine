/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LLayout.hpp"

// Pointer to background
LBackground *background;

// Pointer to drums
LDrum *drums[DRUMS_COUNT];

// Pointer to button
LButton *button;

// Pointer to FPSText
LFPSText *FPSText;

// LLayout constructor
LLayout::LLayout() {
  // Init background
  background = new LBackground();

  // Init drums
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    drums[i] = new LDrum(i);
  }

  // Init FPSText
  FPSText = new LFPSText();

  // Init button
  button = new LButton();
}

// LLayout destructor
LLayout::~LLayout() {
  // Free background
  delete background;

  // Free drums
  for (int i = 0; i < DRUMS_COUNT; ++i) {
    delete drums[i];
  }

  // Free FPSText
  delete FPSText;

  // Init button
  delete button;
}
