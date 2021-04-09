#include <janet.h>

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#include <unistd.h>
#include <stdlib.h>

int testImage(SDL_Renderer* renderer, const char* fileName)
{
  SDL_Surface *image = IMG_Load(fileName);
  if (!image)
  {
     printf("IMG_Load: %s\n", IMG_GetError());
     return 0;
  }
  int result = image->w;

  /**
   * position and size that you wish the image to be copied
   * to on the renderer:
   */
  SDL_Rect dest = {.x = 200, .y = 100, .w = 200, .h = 200};

  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, image);

  SDL_RenderCopy (renderer, tex, NULL, &dest);

  /**
   * Now that the image data is in the renderer, we can free the memory
   * used by the texture and the image surface
   */
  SDL_DestroyTexture (tex);

  SDL_FreeSurface (image);

  return result;
}

static Janet sdl_init_wrap (int32_t argc, Janet *argv)
{
  janet_fixarity (argc, 0);
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window;
  SDL_Renderer *renderer;

  SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);

  int result = 0;

  /**
   * Set up a white background
   */
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  /**
   * Load and copy the test image to the renderer
   */
  result |= testImage(renderer, "assets/logo.png");

  /**
   * Show what is in the renderer
   */
  SDL_RenderPresent(renderer);

  printf("you should see an image.\n");

  return janet_wrap_nil ();
}

static const JanetReg sdl2_cfuns[] = {
  {"sdl-init", sdl_init_wrap, "todo"},
  {NULL, NULL, NULL}
};
