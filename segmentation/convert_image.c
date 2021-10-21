#include <err.h>
#include <stdint.h>
#include "/usr/include/SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "headers/pixel_operations.h"
#include "headers/struct.h"
#include "headers/rlsa.h" //a enlever à la fin
#include "../Pre-traitement/pixel_operations.h"
#include "../Pre-traitement/Filter.h"

int * to_array(SDL_Surface *image_surface, int width, int height)
{
    int size = width * height;
    int image_array[size];
    int *image_array_ptr = image_array;
    Uint32 pixel_value;
    Uint8 r, g, b;


    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            pixel_value = get_pixel(image_surface, j, i);
            SDL_GetRGB(pixel_value, image_surface->format, &r, &g, &b);

            if(r == 0){
                image_array[i * width + j] = 1;
            }

            else{
                image_array[i * width + j] =0;
            } /* put in the corresponding box on the array: 1 if black, 0 if white*/
        }
    }

    return image_array_ptr;
}

Array * main_sdl(char *path)
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    int width;
    int height;
    int *image_array_p;


    init_sdl();
    image_surface = load_image(path);
    screen_surface = display_image(image_surface);

    wait_for_keypressed();
    grayscale(image_surface);
    blackNwhite(image_surface, 127);

    width = image_surface -> w;
    height = image_surface -> h;

    //from b&w to array
    image_array_p = malloc(sizeof(int) * (width * height));
    image_array_p = to_array(image_surface, width, height);

    Array *picture;

    picture = malloc(sizeof(Array));

    if(picture == NULL)
        errx(1, "Array null");

    else
    {
        picture -> width = width;
        picture-> height = height;
        picture -> array = malloc(sizeof(int) * (width * height));
        picture -> array = image_array_p;
    }

    SDL_FreeSurface(image_surface);
    return picture;
}
