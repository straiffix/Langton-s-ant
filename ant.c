#include "antpng.h"
#include "ant.h"

int SetAnt(enum Color* MatrixArray, ant_t *ant) {
	//Sprawdzanie, czy mrуwka nie wyszla poza tablicy
	//Jesli wyszla - idzie dalej :) 
	if (ant->x >= width)
		ant->x-=width;
	if (ant->y >= height)
		ant->y-=height;
	if (ant->x <= 0)
		ant->x+=width;
	if (ant->y <= 0)
		ant->y+=height;
	enum Color currentColor = matrix(ant->x, ant->y);

	//zmiana koloru na przeciwny
	if (currentColor == WHITE) {
		matrix(ant->x, ant->y) = BLACK;
	}
	else {
		matrix(ant->x, ant->y) = WHITE;
	}

	//zmiana koloru na przeciwny
	if (currentColor == WHITE) {
		(ant->antDirection)--; //Tu zmieniłam
		if (ant->antDirection < 0)
			ant->antDirection = LEFT; 
	}
	else if (currentColor == BLACK) {
		(ant->antDirection)++;
		if (ant->antDirection > 3) 
			ant->antDirection = UP; 
	}

	//zmiana kierunku
	if (ant->antDirection == UP) {	
		ant->y--;	
	}
	else if (ant->antDirection == DOWN) {
		ant->y++;
	}
	else if (ant->antDirection == LEFT) {
		ant->x--;
	}
	else if (ant->antDirection == RIGHT) {
		ant->x++;		
	}

	return 0;
}

int LangtonAnt(ant_t ants[], int numberOfAnts, int numberOfSteps, void (*returnProgress)(int, int), int(*saveFunction)(enum Color*, char * name), char * name) {
	enum Color* MatrixArray = (enum Color*)malloc(sizeof(enum Color)* height * width);
	//zerowanie planszy
	int x;
	for (x = 0; x < width; x++) {
		int y;
		for (y = 0; y < height; y++) {
			matrix(x, y) = WHITE;
		}
	}

	int result;
	int i;
	for (i = 0; i < numberOfSteps; i++) {
		int j;
		for (j = 0; j < numberOfAnts; j++) {
		//dla kaїdej mrуwki ustal nowa jej pozycje
			result = SetAnt(MatrixArray, &ants[j]);
			if (result != 0) {
				free(MatrixArray);
				return result;
				continue;
			}
		}
		if (i % 50 == 0) {
			returnProgress(i, numberOfSteps);
		}
	}
	result = saveFunction(MatrixArray, name);
	if (result != 0) {
		return result;
		}
	free(MatrixArray);
	return 0;
}
