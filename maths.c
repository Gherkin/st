#include "maths.h"

double avg(double* points, short size) {
  double sum = 0;
  for (short i = 0; i < size; ++i) {
    sum += *(points + i);
  }

  return (double)sum / size;
}

double median(double* points, short size) {
  return 0;
}
