// Mrowka Langtona.cpp : Defines the entry point for the console application.
//

#include "png.h"
#include "antpng.h"

#define ERROR_OUT_OF_MATRIX -2
#define ERROR_WRITE_FILE -1

#define matrix(x,y) MatrixArray[(y)*height+(x)]


int main(int argc, char **argv){
	int steps;
	char *result;
	int antNum;
	printf("Witaj w programie do symulowania poruszania sie mrowki Langtona\n");
	FILE *in = fopen (argv[2], "r");
	if (in==NULL){
		printf("Konfiguracyjny plik nie istnieje\n");
		exit(EXIT_FAILURE);
		}
	fscanf(in, "%d%d%d%d", &antNum, &height, &width, &steps);
	int i;
	ant_t *ants = malloc(antNum*sizeof(ant_t));
	for(i=0; i<antNum; i++)
		fscanf(in, "%d%d%d", &ants[i].x, &ants[i].y, &ants[i].antDirection);	
	printf("Rozpoczynanie symulacji...");
	LangtonAnt(ants, antNum,  steps, &ReturnProgress, &SaveMatrix, argv[4]);
	free(ants);
	fclose(in);
	printf("\n");
	return 0;
}
