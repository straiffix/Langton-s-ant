#ifndef ANTPNG_H
#define ANTPNG_H

#include <png.h>
#include "ant.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

#define ERROR_OUT_OF_MATRIX -2
#define ERROR_WRITE_FILE -1

#define matrix(x,y) MatrixArray[(y)*height+(x)]


int png_x, png_y;

int width, height;

png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

int write_png_file(char* file_name);
int SaveMatrix(enum Color* MatrixArray, char *name);
void ReturnProgress(int value, int numOfSteps);

#endif
