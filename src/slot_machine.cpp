/* Copyright 2022 <Alexander Abrosov> */

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <stdlib.h>

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  SDL_Window *window =
      SDL_CreateWindow("slot_machine", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 490, SDL_WINDOW_SHOWN);
  SDL_Renderer *gRenderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Color textColor = {0, 255, 0};
  TTF_Font *textFont = TTF_OpenFont("../resources/font.ttf", 18);

  SDL_Surface *image = SDL_LoadBMP("../resources/picture.bmp");
  SDL_Surface *textSurface = NULL;

  SDL_Texture *groundTexture = SDL_CreateTextureFromSurface(gRenderer, image);
  SDL_Texture *textTexture = NULL;

  SDL_Rect cameraPosition = {100, 100, 300, 300};
  SDL_Rect textPosition = {5, 450, 100, 20};
  SDL_Rect minimap = {540, 0, 100, 100};
  SDL_Rect brickVision = {563, 13, 45, 45};
  SDL_Event e;
  int quit = 0, x = 330, y = 240;

  char *inputText;
  inputText = reinterpret_cast<char *>(malloc(40));
  int lengthText = 0;

  while (!quit) {
    SDL_StartTextInput();

    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = 1;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_UP:
          if (cameraPosition.y > 0)
            cameraPosition.y = cameraPosition.y - 5;
          brickVision.y = brickVision.y - 1;
          break;

        case SDLK_DOWN:
          if (cameraPosition.y < 200)
            cameraPosition.y = cameraPosition.y + 5;
          brickVision.y = brickVision.y + 1;
          break;

        case SDLK_LEFT:
          if (cameraPosition.x >= 0)
            cameraPosition.x = cameraPosition.x - 5;
          brickVision.x = brickVision.x - 1;
          break;

        case SDLK_RIGHT:

          if (cameraPosition.x < 340)
            cameraPosition.x = cameraPosition.x + 5;
          brickVision.x = brickVision.x + 1;
          break;

        case SDLK_RETURN:
          if (lengthText > 0) {
            *inputText = '\0';
            inputText -= lengthText;
            textSurface = TTF_RenderText_Solid(textFont, inputText, textColor);
            textPosition.w = textSurface->w;
            textPosition.h = textSurface->h;
            textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            lengthText = 0;
          }

          break;
        }

      } else if (e.type == SDL_TEXTINPUT) {
        *inputText = *e.text.text;
        inputText++;
        lengthText++;

      } else if (e.type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&x, &y);
      }
    }

    if (x < 105 && cameraPosition.x >= 0) {
      cameraPosition.x = cameraPosition.x - 5;
      brickVision.x = brickVision.x - 1;

      SDL_Delay(10);
    }
    if (x > 505 && cameraPosition.x < 340) {
      cameraPosition.x = cameraPosition.x + 5;
      brickVision.x = brickVision.x + 1;

      SDL_Delay(10);
    }
    if (y < 100 && cameraPosition.y >= 0) {
      brickVision.y = brickVision.y - 1;
      cameraPosition.y = cameraPosition.y - 5;
      SDL_Delay(10);
    }
    if (y > 360 && cameraPosition.y < 210) {
      brickVision.y = brickVision.y + 1;
      cameraPosition.y = cameraPosition.y + 5;
      SDL_Delay(10);
    }
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, groundTexture, &cameraPosition, NULL);

    SDL_RenderCopy(gRenderer, groundTexture, NULL, &minimap);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawRect(gRenderer, &brickVision);
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textPosition);
    SDL_RenderPresent(gRenderer);

    SDL_StopTextInput();
  }
  SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}
