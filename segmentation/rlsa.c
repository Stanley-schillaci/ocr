#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "headers/struct.h" //a enlever car se trouve aussi dans rlsa.h

int * rlsa_horizontal(Array *array, int c)
{
    int * y = malloc(sizeof(int) * (array -> width * array -> height)); //pour réserver assez de mémoire
    int nb_zeros_around;
    int k;
    int b = 1;

    for(int i = 0; i < array -> height; i++){

        for(int j = 0; j < array -> width; j++){

            //check if the pixel[i][j] is a 0 or not
            if(array -> array[i * array -> width + j] == 0){

                nb_zeros_around = 0;
                b = 1;
                k = j - 1;

                //check if the number of 0 on the line before the element [i][j] and stop if it found a 1 or when it is the beginning of the array
                while(k >= 0 && nb_zeros_around <= c + 1 && b){

                    if( array -> array[i * array -> width + k] == 0){
                        nb_zeros_around++;
                    }

                    else{
                        b = 0;
                    }

                    k--;
                }

                b = 1;
                k = j + 1;

                while(k < array -> width && nb_zeros_around <= c + 1 && b){ //do the same of the first loop but do the research from the element j to the end of the line

                    if( array -> array[i * array -> width + k] == 0){
                        nb_zeros_around++;
                    }

                    else{
                        b = 0;
                    }

                    k++;
                }
                if( nb_zeros_around < c){ //replace by a pixel black if c is too big
                    y[i * array -> width + j] = 1;
                }

                else{
                    y[i * array -> width + j] = 0;
                }
            }
            else{
                y[i * array -> width + j] = 1;
            }

        }
    }

    return y;
}


int * rlsa_vertical(Array *array, int c)
{
    int * y = malloc(sizeof(int) * (array -> width * array -> height)); //For the memory
    int nb_zeros_around;
    int k;
    int b = 1;

    for(int i = 0; i < array -> width; i++){

        for(int j = 0; j < array -> height; j++){

            //chek if the element[i][j] is a 0 or a 1
            if(array -> array[j * array -> width + i] == 0){

                nb_zeros_around = 0;
                b = 1;
                k = j - 1;

                //check the number of 0 on the column k and stop if it found a 1 or arrived to the first column
                while(k >= 0 && nb_zeros_around <= c + 1 && b){

                    if( array -> array[k * array -> width + i] == 0) {
                        nb_zeros_around++;
                    }

                    else{
                        b = 0;
                    }

                    k--;
                }

                b = 1;
                k = j + 1;

                //do the same but with the second part of the image
                while(k < array -> width && nb_zeros_around <= c + 1 && b){

                    if( array -> array[k * array -> width + j] == 0){
                        nb_zeros_around++;
                    }

                    else{
                        b = 0;
                    }

                    k++;
                }

                if(nb_zeros_around < c) {//replace the pixel black if c is too big
                    y[j * array->width + i] = 1;
                }

                else {
                    y[j * array->width + i] = 0;
                }
            }
            else{
                y[j * array -> width + i] = 1;
            }
        }
    }

    return y;
}

int * rlsa_combine(int *horizontal, int * vertical, size_t size) //the final result is the combination of horizontal and the vertical with a AND
{
    int * combine = malloc(sizeof(int) * (size));

    for(size_t i = 0; i < size; i++){
        combine[i] = horizontal[i] && vertical[i];
    }

    return combine;
}


/* 
-Take the binarize image is an array of 1 and 0
-Create two array corresponding to the rlsa vertical and rlsa horizontal
-Combine the both with a AND
-return the final rlsa
*/
Array * main_rlsa(Array * array)
{

    int *horizontal = rlsa_horizontal(array, 50);
    int *vertical = rlsa_vertical(array, 100);

    Array *combined = malloc(sizeof(Array));

    if(combined == NULL){
        errx(1, "Combined null");
    }

    else
    {
        combined->width = array->width;
        combined->height = array->height;
        combined->array = rlsa_combine(horizontal, vertical, array -> width * array -> height);
    }
    free(horizontal);
    free(vertical);

    return combined;
}
