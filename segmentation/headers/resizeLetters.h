#ifndef RESIZELETTERS_H_
#define RESIZELETTERS_H_

#include <stdlib.h>
#include "struct.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))




void cropH(Letter * l);
void cropW(Letter * l);
void scaleUp(Letter * l);
void corner(Letter * l);
void addWhiteLine(Letter * l);
void addWhiteCollumn(Letter * l);
void resize(Letter * l);
void reduce(Letter * l);
void process(Letter ** letterList);
void main_resize();

#endif

