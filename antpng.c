
#include "antpng.h"

int write_png_file(char* file_name) {
  FILE *fp = fopen(file_name, "wb");
  if (!fp){
    printf("[write_png_file] File %s could not be opened for writing", file_name);
    return ERROR_WRITE_FILE;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr){
    printf("[write_png_file] png_create_write_struct failed");
    return ERROR_WRITE_FILE;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr){
    printf("[write_png_file] png_create_info_struct failed");
    return ERROR_WRITE_FILE;
  }

  if (setjmp(png_jmpbuf(png_ptr))){
    printf("[write_png_file] Error during init_io");
    return ERROR_WRITE_FILE;
  }

  png_init_io(png_ptr, fp);

  if (setjmp(png_jmpbuf(png_ptr))){
    printf("[write_png_file] Error during writing header");
    return ERROR_WRITE_FILE;
  }

  png_set_IHDR(png_ptr, info_ptr, width, height,
   bit_depth, color_type, PNG_INTERLACE_NONE,
   PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr))){
    printf("[write_png_file] Error during writing bytes");
    return ERROR_WRITE_FILE;
  }

  png_write_image(png_ptr, row_pointers);

  if (setjmp(png_jmpbuf(png_ptr))){
    printf("[write_png_file] Error during end of write");
    return ERROR_WRITE_FILE;
  }

  png_write_end(png_ptr, NULL);

   fclose(fp);

  png_destroy_write_struct(&png_ptr, &info_ptr);

  for (png_y=0; png_y<height; png_y++)
    free(row_pointers[png_y]);
  free(row_pointers);
  return 0;
}

int SaveMatrix(enum Color* MatrixArray, char *name) {
  bit_depth = 8;
  color_type = PNG_COLOR_TYPE_GRAY;

  number_of_passes = 7;
  row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
  if(row_pointers == 0){
    return ERROR_WRITE_FILE;
  }

  for (png_y=0; png_y<height; png_y++){
    row_pointers[png_y] = (png_byte*) malloc(sizeof(png_byte) * width);
    if(row_pointers[png_y] == 0){
      return ERROR_WRITE_FILE;
    }
  }

  for (png_y=0; png_y<height; png_y++) {
    png_byte* row = row_pointers[png_y];
    for (png_x=0; png_x<width; png_x++) {
      if(matrix(png_y, png_x)==WHITE)
		row[png_x] = 255;
	else
		row[png_x] = 80;
    }
  }
	return write_png_file(name);
}


void ReturnProgress(int value, int numOfSteps) {
	printf("\r[\033[0;31m");
	int percentage = value*50/numOfSteps;
	for(int i=0;i<percentage;i++){
		printf("\u25a0");
	}
	for(int i=0; i< 50-percentage;i++){
		printf("-");
	}
	printf("\033[0m]%d%%",(value*100/numOfSteps));
	fflush(stdout);
}


