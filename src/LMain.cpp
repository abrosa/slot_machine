/* Copyright 2022 <Alexander Abrosov> */

#include "../include/LMain.hpp"

// Pointer to rotation
LApplication *application;

// Pointer to rotation
LLayout *layout;

// Pointer to rotation
LRotation *rotation;

// Pointer to render
LRender *render;

// Pointer to timer
LTimer *timer;

// LMain constructor
LMain::LMain() {
  // Init application
  application = new LApplication();

  // Init layout
  layout = new LLayout();

  // Init rotation
  rotation = new LRotation();

  // Init render
  render = new LRender();

  // Init timer
  timer = new LTimer();
}

// LMain destructor
LMain::~LMain() {
  // Free timer
  delete timer;

  // Free render
  delete render;

  // Free rotation
  delete rotation;

  // Free layout
  delete layout;

  // Free application
  delete application;
}
