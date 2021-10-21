#ifndef SPLIT_H
#define SPLIT_H

void split_horizontal(Array * mat);
void split_vertical(Array * mat);
Array * letter(Array * mat, int x, int y);
Letter ** list_elmnt(Array * mat);

#endif
