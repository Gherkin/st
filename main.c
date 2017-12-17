#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "maths.h"

#define MALLOC_SEG 1024

typedef struct point {
  double data;
  char* key;
} point;

int tokenize(char* str, char** data_ptr) {
  for(int i = 0; i < strlen(str); ++i) {
    if(str[i] == ' ') {
      str[i] = '\0';
      *data_ptr = &str[i] + 1;
      return 0;
    }
  }

  return 1;
}

int readdata(point* pointbuf) {
  size_t size = 1;
  if (getline(&(pointbuf->key), &size, stdin) == -1) {
    return 1;
  }
  
  char* data_ptr = NULL;
  tokenize(pointbuf->key, &data_ptr);
  sscanf(data_ptr, "%lf", &pointbuf->data);

  return 0;
}

int readkeystruct(double** points, short point_len, point** pointbuf) {
  char* key;
  short i = 0;
  int exitcode;
  if(strlen((*pointbuf)->key) < 1) {
    readdata(*pointbuf);
  } 

  //TODO reuse
  key = malloc((strlen((*pointbuf)->key) + 1) * sizeof(char));
  strcpy(key, (*pointbuf)->key);
  **points = (*pointbuf)->data;
  ++i;



  while ((exitcode = readdata(*pointbuf)) != 1) {
    if(i + 1 >= point_len ) {
      *points = realloc(*points, point_len + MALLOC_SEG);
      point_len += MALLOC_SEG;
    }
    if(strcmp(key, (*pointbuf)->key)) {
      break;
    }
    *(*points + i) = (*pointbuf)->data;
    i++;
  }

  printf("%s %lf %lf\n", key, avg(*points, i), median(*points, i));
  free(key);
  return exitcode;
}

int main(int argc, char **argv) {
  double* points = malloc(sizeof(double) * MALLOC_SEG);
  short len = 1;

  point* pointbuf;
  pointbuf = malloc(sizeof(point));
  pointbuf->key = malloc(sizeof(char) * MALLOC_SEG);
  memset(pointbuf->key, 0, 1);

  while (readkeystruct(&points, len, &pointbuf) != 1) {
    (void)0;
  }

  free(pointbuf->key);
  free(pointbuf);
  free(points);

  return 0;
}
