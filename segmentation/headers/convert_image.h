#ifndef CONVERT_IMAGE_H
#define CONVERT_IMAGE_H
#include "SDL.h"
#include "SDL_image.h"
/*#include "/usr/include/SDL/SDL.h"
#include "SDL/SDL_image.h"*/
#include "struct.h"

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();
SDL_Surface* to_grayscale(SDL_Surface *image_surface, int width, int height, Uint32 *pixel_average/*, Uint32 *max, Uint32 *min*/);
SDL_Surface* to_black_and_white (SDL_Surface *image_surface, int width, int height, Uint32 *pixel_average/*Uint32 *min, Uint32 *max*/);
int * to_array(SDL_Surface *image_surface, int width, int height);
Array * main_sdl(char path[]);

#endif
