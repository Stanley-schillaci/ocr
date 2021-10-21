#ifndef FILTER_H
#define FILTER_H_

#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "pixel_operations.h"

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();
void grayscale(SDL_Surface* l);
Uint32 CheckCorners(SDL_Surface* l, int x, int y, int lim);
void filter(SDL_Surface* l, int lim);
SDL_Surface* SDL_RotationCentral(SDL_Surface* origin, float angle);
void SDL_FreeSurface(SDL_Surface *surface);
void digitalProcess(char *filename);
void blackNwhite(SDL_Surface* image_surface, float thresold);

#endif
