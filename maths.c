#include "maths.h"
#include <stdlib.h>

double avg(double* points, short size) {
  double sum = 0;
  for (short i = 0; i < size; ++i) {
    sum += *(points + i);
  }

  return (double)sum / size;
}

int compare_doubles(const void* a, const void* b) {
  const double* da = (const double*) a;
  const double* db = (const double*) b;

  return (*da > *db) - (*da < *db);
}

double median(double* points, short size) {
  qsort (points, size, sizeof (double), compare_doubles);
  if (size % 2 == 0) {
    return (points[size / 2 - 1] + points[(size + 2) / 2 - 1]) / 2;
  } else {
    return points[size / 2];
  }
}
