#include <stdio.h>
#include<stdlib.h>
#include <err.h>
#include "headers/struct.h"

//draw horizontal line where there is no pixel
void split_horizontal(Array * mat)
{
    int b = 1;
    int j;
    for(int i = 0; i < mat->height ; i++)
    {
        b = 1;
        j = 0;
        while(j < mat->width && b)
        {
            if(mat->array[i * mat->width + j] == 1)
            {
                b = 0;
            }
            else{
                b = 1;
            }
            j++;
        }
        if(b)
        {
            for(int k = 0; k < mat->width; k++)
            {
                mat->array[i * mat->width + k] = 2;
            }
        }
    }
}

//draw vertical line between two horizontal line where there is no character
void split_vertical(Array * mat)
{
    int b;
    int last_j = 0;
    for(int i = 0; i < mat->width ; i++)
    {
        b = 1;
        for(int j = 0; j < mat->height; j++)
        {
            if(mat->array[j * mat->width + i] == 2 && (j - last_j) > 1)
            {
                if(b)
                {
                    for(int k = last_j + 1; k < j; k++)
                    {
                        mat->array[k * mat->width + i] = 3;
                    }
                }
                b = 1;
                last_j = j;
            }

            else if(mat->array[j * mat->width + i] == 2 && (j - last_j) <= 1)
            {
                last_j = j;
            }

            else if(mat->array[j * mat->width + i] == 1)
            {
                b = 0;
            }
        }
    }
}

Letter * letter(Array * mat, int x, int y)
{
    int width = 0;
    int height = 0;
    int b = 1;
    int i = 0;
    int j = 0;
    Letter *ret;
    ret = malloc(sizeof(Letter));

    //found the  heigth of a character
    while((i + y) < mat->height && b)
    {
        if(mat->array[mat->width * (y + i) + x] == 0 || mat->array[mat->width * (y + i) + x] == 1)
        {
            height++;
        }
        else
        {
            b = 0;
        }
        i++;
    }

    b = 1;

    //found the width of a character
    while((j + x) < mat->width && b)
    {
        if(mat->array[mat->width * y + x + j] == 0 || mat->array[mat->width * y + x + j] == 1)
        {
            width++;
        }
        else
        {
            b = 0;
        }
        j++;
    }

    ret->array = malloc(sizeof(int) * (width * height));
    ret->width = width;
    ret->height = height;
    ret->x = x;
    ret->y = y;

    for(int k =0; k < ret->height; k++)
    {
        for(int u = 0; u < ret->width; u++)
        {
            ret->array[width * k + u] = mat->array[mat->width * (y + k) + (x + u)];// ret takes the value of the character's array
            mat->array[mat->width * (y + k) + (x + u)] = 4; //to say we visited this pixel
        }
    }
    return ret;
}

//Create the list of all element of the text
Letter ** list_elmnt(Array * mat)
{
    Letter ** list = malloc(sizeof(Letter) * (mat->width * mat->height));
    int idx = 0;
    int b = 1;

    for(int i = 0; i < mat->height ; i++)
    {
        if(mat->array[i * mat->width] != 2) //if line is not empty (not red)
        {
            for(int j = 0; j < mat->width; j++)
            {
                if(((mat->array[i * mat->width + j] == 1) || (mat->array[i * mat->width + j] == 0)) && b)// if we found a character
                {
                    list[idx] = letter(mat, j, i);
                    b = 0;
                    idx++;
                }
                else if (mat->array[i * mat->width + j] == 3)
                {
                    b = 1;
                }
            }
        }
    }
    return list;
}
  
  
