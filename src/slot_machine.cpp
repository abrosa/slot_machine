/* Copyright 2022 <Alexander Abrosov> */

// #include <stdlib.h>

#include "../include/slot_machine.hpp"

#include <sstream>

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Texture wrapper class
class LTexture {
 public:
  // Initializes variables
  LTexture();

  // Deallocates memory
  ~LTexture();

  // Loads image at specified path
  bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
  // Creates image from font string
  bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

  // Deallocates texture
  void free();

  // Set color modulation
  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  // Set blending
  void setBlendMode(SDL_BlendMode blending);

  // Set alpha modulation
  void setAlpha(Uint8 alpha);

  // Renders texture at given point
  void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0,
              SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Gets image dimensions
  int getWidth();
  int getHeight();

 private:
  // The actual hardware texture
  SDL_Texture *mTexture;

  // Image dimensions
  int mWidth;
  int mHeight;
};

// The application time based timer
class LTimer {
 public:
  // Initializes variables
  LTimer();

  // The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();

  // Gets the timer's time
  Uint32 getTicks();

  // Checks the status of the timer
  bool isStarted();
  bool isPaused();

 private:
  // The clock time when the timer started
  Uint32 mStartTicks;

  // The ticks stored when the timer was paused
  Uint32 mPausedTicks;

  // The timer status
  bool mPaused;
  bool mStarted;
};

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Globally used font
TTF_Font *gFont = NULL;

// Scene textures
LTexture gFPSTextTexture;

LTexture::LTexture() {
  // Initialize
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() {
  // Deallocate
  free();
}

bool LTexture::loadFromFile(std::string path) {
  // Get rid of preexisting texture
  free();

  // The final texture
  SDL_Texture *newTexture = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    // Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

    // Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    } else {
      // Get image dimensions
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  // Return success
  mTexture = newTexture;
  return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText,
                                    SDL_Color textColor) {
  // Get rid of preexisting texture
  free();

  // Render text surface
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
  if (textSurface != NULL) {
    // Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (mTexture == NULL) {
      printf("Unable to create texture from rendered text! SDL Error: %s\n",
             SDL_GetError());
    } else {
      // Get image dimensions
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }

    // Get rid of old surface
    SDL_FreeSurface(textSurface);
  } else {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
  }

  // Return success
  return mTexture != NULL;
}
#endif

void LTexture::free() {
  // Free texture if it exists
  if (mTexture != NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  // Modulate texture rgb
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
  // Set blending function
  SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
  // Modulate texture alpha
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle,
                      SDL_Point *center, SDL_RendererFlip flip) {
  // Set rendering space and render to screen
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  // Set clip rendering dimensions
  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  // Render to screen
  SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }

LTimer::LTimer() {
  // Initialize the variables
  mStartTicks = 0;
  mPausedTicks = 0;

  mPaused = false;
  mStarted = false;
}

void LTimer::start() {
  // Start the timer
  mStarted = true;

  // Unpause the timer
  mPaused = false;

  // Get the current clock time
  mStartTicks = SDL_GetTicks();
  mPausedTicks = 0;
}

void LTimer::stop() {
  // Stop the timer
  mStarted = false;

  // Unpause the timer
  mPaused = false;

  // Clear tick variables
  mStartTicks = 0;
  mPausedTicks = 0;
}

void LTimer::pause() {
  // If the timer is running and isn't already paused
  if (mStarted && !mPaused) {
    // Pause the timer
    mPaused = true;

    // Calculate the paused ticks
    mPausedTicks = SDL_GetTicks() - mStartTicks;
    mStartTicks = 0;
  }
}

void LTimer::unpause() {
  // If the timer is running and paused
  if (mStarted && mPaused) {
    // Unpause the timer
    mPaused = false;

    // Reset the starting ticks
    mStartTicks = SDL_GetTicks() - mPausedTicks;

    // Reset the paused ticks
    mPausedTicks = 0;
  }
}

Uint32 LTimer::getTicks() {
  // The actual timer time
  Uint32 time = 0;

  // If the timer is running
  if (mStarted) {
    // If the timer is paused
    if (mPaused) {
      // Return the number of ticks when the timer was paused
      time = mPausedTicks;
    } else {
      // Return the current time minus the start time
      time = SDL_GetTicks() - mStartTicks;
    }
  }

  return time;
}

bool LTimer::isStarted() {
  // Timer is running and paused or unpaused
  return mStarted;
}

bool LTimer::isPaused() {
  // Timer is running and paused
  return mPaused && mStarted;
}

bool init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }

    // Create window
    gWindow = SDL_CreateWindow("slot_machine", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Create vsynced renderer for window
      gRenderer = SDL_CreateRenderer(
          gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        success = false;
      } else {
        // Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          success = false;
        }

        // Initialize SDL_ttf
        if (TTF_Init() == -1) {
          printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
                 TTF_GetError());
          success = false;
        }
      }
    }
  }

  return success;
}

bool loadMedia() {
  // Loading success flag
  bool success = true;

  // Open the font
  gFont = TTF_OpenFont("../resources/font.ttf", 18);
  if (gFont == NULL) {
    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    success = false;
  }

  return success;
}

void close() {
  // Free loaded images
  gFPSTextTexture.free();

  // Free global font
  TTF_CloseFont(gFont);
  gFont = NULL;

  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

int main(int argc, char *args[]) {
  // Start up SDL and create window
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    // Load media
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
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

      // SDL_Surface *textSurface = NULL;
      // SDL_Texture *textTexture = NULL;

      SDL_Surface *background = IMG_Load("../resources/bg.png");
      SDL_Texture *groundTexture =
          SDL_CreateTextureFromSurface(gRenderer, background);

      SDL_Surface *image = IMG_Load("../resources/drum.png");
      SDL_Texture *drumTexture = SDL_CreateTextureFromSurface(gRenderer, image);

      SDL_Rect drum1 = {0, 40, 85, 240};
      SDL_Rect drum2 = {0, 40, 85, 240};
      SDL_Rect drum3 = {0, 40, 85, 240};
      SDL_Rect drum4 = {0, 40, 85, 240};
      SDL_Rect drum5 = {0, 40, 85, 240};

      SDL_Rect viewpoint1 = {50, 50, 85, 240};
      SDL_Rect viewpoint2 = {150, 50, 85, 240};
      SDL_Rect viewpoint3 = {250, 50, 85, 240};
      SDL_Rect viewpoint4 = {350, 50, 85, 240};
      SDL_Rect viewpoint5 = {450, 50, 85, 240};

      // While application is running
      while (!quit) {
        // SDL_StartTextInput();
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

        // Render three drums
        SDL_RenderCopy(gRenderer, drumTexture, &drum1, &viewpoint1);
        SDL_RenderCopy(gRenderer, drumTexture, &drum2, &viewpoint2);
        SDL_RenderCopy(gRenderer, drumTexture, &drum3, &viewpoint3);
        SDL_RenderCopy(gRenderer, drumTexture, &drum4, &viewpoint4);
        SDL_RenderCopy(gRenderer, drumTexture, &drum5, &viewpoint5);

        // Render FPS
        gFPSTextTexture.render(20, 420);

        // Update screen
        SDL_RenderPresent(gRenderer);
        // SDL_StopTextInput();
        ++countedFrames;
      }
    }
  }
  // ???
  // SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

  // Free resources and close SDL
  close();

  return 0;
}
