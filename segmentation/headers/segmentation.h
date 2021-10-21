#ifndef NEWTEST_SEGMENTATION_H
#define NEWTEST_SEGMENTATION_H


void array_to_image(Array * array, char path[]);
void print_matrix(Array * array);
void averages_height_and_spaces(Letter ** list, int *average_spaces, int *average_height);
void segmentation(char *filename);

#endif
