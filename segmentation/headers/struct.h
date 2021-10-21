#ifndef STRUCT_ARRAY_H
#define STRUCT_ARRAY_H

typedef struct Array Array;
struct Array
{
  int width;
  int height;
  int *array;
};

typedef struct Letter Letter;
struct Letter
{
  int width;
  int height;
  int width_init;
  int height_init;
  int x;
  int y;
  char c; //takes value of the result of the neural network
  int *array;
};
#endif
