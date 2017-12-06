#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 128
#define MALLOC_SEG

typedef struct point {
  double data;
  char* key;
} point;

int tokenize(char* str, char* token1, char* token2) {
  short i = 0;
  short k = 0;

  while(str[i] != ' ') {
    if(str[i] == '\0') {
      return 1;
    }
    token1[i] = str[i];
    i++;
  }
  i++;

  while(str[i] != '\0') {
    if(str[i] != '\n') {
      token2[k] = str[i];
    }
    k++;
    i++;
  }

  return 0;
}

int readdata(point* pointbuf) {
  size_t size;
  char* strbuf = malloc(sizeof(char) * STRING_SIZE);
  if (getline(&strbuf, &size, stdin) == -1) {
    free(strbuf);
    return 1;
  }
  
  char* databuf = malloc((strlen(strbuf) + 1) * sizeof(char));
  tokenize(strbuf, pointbuf->key, databuf);
  sscanf(databuf, "%lf", &pointbuf->data);

  free(databuf);
  free(strbuf);
  return 0;
}

double avg(double* points, short point_len) {
  double sum = 0;
  for (short i = 0; i < point_len; ++i) {
    sum += *(points + i);
  }

  return (double)sum / point_len;
}

int readkeystruct(double* points, short point_len, point** pointbuf_ptr) {
  char* key;
  short i = 0;
  point* pointbuf = *pointbuf_ptr;
  int exitcode;
  if(strlen(pointbuf->key) < 1) {
    readdata(pointbuf);
  } 

  key = malloc((strlen(pointbuf->key) + 1) * sizeof(char));
  strcpy(key, pointbuf->key);
  *points = pointbuf->data;
  ++i;

  //puts(key);


  while ((exitcode = readdata(pointbuf)) != 1) {
    if(strcmp(key, pointbuf->key)) {
      break;
    }
    *(points + i) = pointbuf->data;
    i++;
  }
  //for (int k = 0; k < i; ++k) {
  //  printf("s=%lf\n", *(points + k));
  //}

  printf("%s %lf\n", key, avg(points, i));
  free(key);
  return exitcode;
}

int main() {
  double* points = malloc(sizeof(double) * 5000);
  short len = 5000;
  point* pointbuf;
  pointbuf = malloc(sizeof(point));
  pointbuf->key = malloc(sizeof(char) * STRING_SIZE * 5000);
  *(pointbuf->key) = '\0';
  while (readkeystruct(points, len, &pointbuf) != 1) {
    (void)0;
  }
  free(pointbuf->key);
  free(pointbuf);
  free(points);
}
