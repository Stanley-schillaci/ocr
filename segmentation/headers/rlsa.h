#ifndef RLSA_H
#define RLSA_H

int * rlsa_horizontal(Array *array, int c);
int * rlsa_vertical(Array *array, int c);
int * rlsa_combine(int *horizontal, int * vertical, size_t size);
Array * main_rlsa(Array * array);

#endif
