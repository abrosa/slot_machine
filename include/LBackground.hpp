/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_LBACKGROUND_HPP_
#define INCLUDE_LBACKGROUND_HPP_

// The mouse button
class LBackground {
 public:
  // Initializes internal variables
  LBackground();

  // Render drums
  void render();

  // Load media
  void loadMedia();
};

#endif  // INCLUDE_LBACKGROUND_HPP_
