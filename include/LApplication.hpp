/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LAPPLICATION_HPP_
#define INCLUDE_LAPPLICATION_HPP_

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Margins from the borders
const int MARGIN_X = 40;
const int MARGIN_Y = 40;

// Application class
class LApplication {
 public:
  // Application constructor
  LApplication();

  // Application destructor
  ~LApplication();
};

#endif  // INCLUDE_LAPPLICATION_HPP_
