/* Copyright 2022 <Alexander Abrosov> */

// #include <stdlib.h>

#include "../include/slot_machine.hpp"

#include "../../x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include "../../x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  SDL_Window *window =
      SDL_CreateWindow("slot_machine", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 670, 420, SDL_WINDOW_SHOWN);
  SDL_Renderer *gRenderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Color textColor = {0, 255, 0};

  TTF_Font *textFont = TTF_OpenFont("../resources/font.ttf", 18);
  SDL_Surface *textSurface = NULL;
  SDL_Texture *textTexture = NULL;
  SDL_Rect textPosition = {5, 450, 100, 20};

  SDL_Surface *background = IMG_Load("../resources/picture.bmp");
  SDL_Texture *groundTexture =
      SDL_CreateTextureFromSurface(gRenderer, background);

  SDL_Surface *image = IMG_Load("../resources/drum.png");
  SDL_Texture *drumTexture = SDL_CreateTextureFromSurface(gRenderer, image);
  SDL_Rect drum1 = {0, 80, 170, 320};
  SDL_Rect drum2 = {0, 80, 170, 320};
  SDL_Rect drum3 = {0, 80, 170, 320};
  SDL_Rect viewpoint1 = {50, 50, 170, 320};
  SDL_Rect viewpoint2 = {250, 50, 170, 320};
  SDL_Rect viewpoint3 = {450, 50, 170, 320};

  SDL_Event event;

  int quit = 0;

  char *inputText;
  inputText = reinterpret_cast<char *>(malloc(40));
  int lengthText = 0;

  while (!quit) {
    SDL_StartTextInput();

    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_UP:
            drum1.y -= 5;
            if (drum1.y < 0) {
              drum1.y = 160 * 9;
            }
            break;
          case SDLK_DOWN:
            drum2.y -= 5;
            if (drum2.y < 0) {
              drum2.y = 160 * 9;
            }
            break;
          case SDLK_LEFT:
            drum3.y -= 5;
            if (drum3.y < 0) {
              drum3.y = 160 * 9;
            }
            break;
          case SDLK_RETURN:
            if (lengthText > 0) {
              *inputText = '\0';
              inputText -= lengthText;
              textSurface =
                  TTF_RenderText_Solid(textFont, inputText, textColor);
              textPosition.w = textSurface->w;
              textPosition.h = textSurface->h;
              textTexture =
                  SDL_CreateTextureFromSurface(gRenderer, textSurface);
              lengthText = 0;
            }
            break;
        }
      } else if (event.type == SDL_TEXTINPUT) {
        *inputText = *event.text.text;
        inputText++;
        lengthText++;
        //} else if (event.type == SDL_MOUSEMOTION) {
        //    SDL_GetMouseState(&x, &y);
      }
    }

    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, groundTexture, NULL, NULL);
    SDL_RenderCopy(gRenderer, drumTexture, &drum1, &viewpoint1);
    SDL_RenderCopy(gRenderer, drumTexture, &drum2, &viewpoint2);
    SDL_RenderCopy(gRenderer, drumTexture, &drum3, &viewpoint3);
    // SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    // SDL_RenderDrawRect(gRenderer, &brickVision);
    // SDL_RenderCopy(gRenderer, textTexture, NULL, &textPosition);
    SDL_RenderPresent(gRenderer);
    SDL_StopTextInput();
  }
  SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}
