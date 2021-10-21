#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "headers/struct.h"
#include "headers/pixel_operations.h"
#include "headers/convert_image.h"
#include "headers/rlsa.h"
#include "headers/split.h"
#include "headers/resizeLetters.h"
#include "headers/SDL.h"
#include "headers/SDL_image.h"
#include "../Pre-traitement/Filter.h"
#include "../Pre-traitement/pixel_operations.h"

void array_to_image(Array * array, char path[])// to see the test
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    Uint8 r, g, b;
    Uint32 pixel_value;

    init_sdl();

    image_surface = load_image(path);
    screen_surface = display_image(image_surface);
    wait_for_keypressed();

    for (int i = 0; i < array->height * array->width; i++)
    {

        if (array->array[array->width * (i / array->width) + i % array->width] == 0)
        {
            r = 255;
            g = 255;
            b = 255;
        }
        else if (array->array[array->width * (i /array->width) + i % array->width] == 1)
        {
            r = 0;
            g = 0;
            b = 0;
        }
        else if (array->array[array->width * (i /array->width) + i % array->width] == 2)
        {
            r = 255;
            g = 0;
            b = 0;
        }
        else if (array->array[array->width * (i /array->width) + i % array->width] == 3)
        {
            r = 0;
            g = 0;
            b = 255;
        }
        else
        {
            r = 0;
            g = 255;
            b = 0;
        }

        pixel_value = SDL_MapRGB(image_surface->format, r, g, b);
        put_pixel(image_surface, i % array->width, i / array->width, pixel_value);
    }

    update_surface(screen_surface, image_surface);
    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
}

void print_matrix(Array * array) //to print a matrix
{
    for (int i = 0; i < array->height; i++)
    {
        for (int j = 0; i < array->width; j++)
            printf("%d ", array->array[array->width * i + j]);
        printf("\n");
        wait_for_keypressed();
    }
}

void averages_height_and_spaces(Letter ** list, int *average_spaces, int *average_height)//get the average of spaces betwween word and spaces between line
{
    size_t i = 1;
    int nb_elmnt = 0;

    if(list[0])
    {
        nb_elmnt ++;
        *average_height += list[0]->height_init;

        while(list[i])
        {
            *average_spaces += ((list[i]->x + list[i]->width_init)  - list[i - 1]->x);
            *average_height += list[i]->height_init;
            nb_elmnt++;
            i++;
        }

        *average_spaces /= nb_elmnt;
        *average_height /= nb_elmnt;
    }
}

void write_file(Letter ** list, char *pathname) //write in a file the matrix of character
{
    size_t i = 1;
    FILE *f = fopen(pathname, "w+");
    char s = ' ';
    char r = '\n';

    int average_height = 0;
    int average_spaces = 0;

    int x = 0;
    int y = 0;

    int diff_x = 0;
    int diff_y = 0;

    averages_height_and_spaces(list, &average_spaces, &average_height);

    printf("here");

    if (list[0])
    {




        //fwrite(&list[0]->c, 1, sizeof(char), f);
        fprintf(f, "%c", list[0]->c);
        x = list[0]->x;
        y = list[0]->y;
    }

    while(list[i])
    {
        diff_y = list[i]->y - y;
        diff_x = list[i]->x - x;

        //go to next line
        if (diff_y > average_height)
            for (int j = 0; j < diff_y / average_height; j++)
                //fwrite(&r, 1, sizeof(char), f);
                fprintf(f, "%s",&r);

            //space(no space if return to line)
        else if (diff_x > 0 && diff_x > average_spaces)
        {
            for (int j = 0; j < diff_x / average_spaces; j++)
                //fwrite(&s, 1, sizeof(char), f);
                fprintf(f, "%s",&s);
        }

        //fwrite(/*&c*/&list[i]->c, 1, sizeof(char), f);
        fprintf(f, "%c",list[i]->c);

        x = list[i]->x;
        y = list[i]->y;
        i++;
    }
    fclose(f);
}

void segmentation(char *filename) {
    Array *black_and_white = malloc(sizeof(Array));


    black_and_white = main_sdl(filename);


    Array *combined = malloc(sizeof(Array));
    combined = main_rlsa(black_and_white);

    array_to_image(combined, filename);

    split_horizontal(black_and_white);
    array_to_image(black_and_white, filename);

    split_vertical(black_and_white);
    array_to_image(black_and_white, filename);

    Letter **list = NULL;
    list = list_elmnt(black_and_white);

    array_to_image(black_and_white, filename);

    process(list);

    //write_file(list, "out.txt");

    free(black_and_white);
    free(combined);
}