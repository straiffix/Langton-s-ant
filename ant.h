#ifndef ANT_H
#define ANT_H

#include <png.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

#define ERROR_OUT_OF_MATRIX -2
#define ERROR_WRITE_FILE -1

#define matrix(x,y) MatrixArray[(y)*height+(x)]


enum Color { WHITE, BLACK };

enum Direction { UP, RIGHT, DOWN, LEFT };

typedef struct {
	int x;
	int y;
	int antDirection;
} ant_t;

int SetAnt(enum Color* MatrixArray, ant_t *ant);

int LangtonAnt(ant_t ants[], int numberOfAnts, int numberOfSteps, void (*returnProgress)(int, int), int(*saveFunction)(enum Color*, char * name), char * name);

#endif
