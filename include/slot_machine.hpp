/* Copyright 2022 <Alexander Abrosov> */

#ifndef INCLUDE_SLOT_MACHINE_HPP_
#define INCLUDE_SLOT_MACHINE_HPP_

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

int main(int argc, char *argv[]);

#endif  // INCLUDE_SLOT_MACHINE_HPP_
