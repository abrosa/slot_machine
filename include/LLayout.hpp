/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LLAYOUT_HPP_
#define INCLUDE_LLAYOUT_HPP_

// Geometry constants:

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
// Margins from the borders
const int MARGIN_X = 40;
const int MARGIN_Y = 40;
// Gaps between elements
const int GAP_X = MARGIN_X / 2;
const int GAP_Y = MARGIN_Y / 2;

// Button size
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 80;
// Button position - lower right corner
const int BUTTON_X = SCREEN_WIDTH - MARGIN_X - BUTTON_WIDTH;
const int BUTTON_Y = SCREEN_HEIGHT - MARGIN_Y - BUTTON_HEIGHT;

// FPSText size
// Font = FiraMono-Bold.ttf
// Font size 48 points
// Text example "FPS: 60.000"
// - Pre-calculated with function TTF_SizeText()
const int TEXT_WIDTH = 319;
const int TEXT_HEIGHT = 58;
// Text position - lower left corner
const int TEXT_X = MARGIN_X;
const int TEXT_Y = SCREEN_HEIGHT - MARGIN_Y - TEXT_HEIGHT;

// Footer size
const int FOOTER = (TEXT_HEIGHT > BUTTON_HEIGHT) ? TEXT_HEIGHT : BUTTON_HEIGHT;

// Drums position - upper part of window
// The number of drums
const int DRUMS_COUNT = 5;
// Drums position
const int DRUM_X = MARGIN_X;
const int DRUM_Y = MARGIN_Y;
// Drum width
const int DRUM_WIDTH =
    (SCREEN_WIDTH - 2 * MARGIN_X - (DRUMS_COUNT - 1) * GAP_X) / DRUMS_COUNT;
// Next drum shifted to
const int DRUM_STEP = DRUM_WIDTH + GAP_X;
// Drum height
const int DRUM_HEIGHT = SCREEN_HEIGHT - 2 * MARGIN_Y - FOOTER - GAP_Y;

// LLayout class
class LLayout {
 public:
  // LLayout constructor
  LLayout();

  // LLayout destructor
  ~LLayout();
};

#endif  // INCLUDE_LLAYOUT_HPP_
