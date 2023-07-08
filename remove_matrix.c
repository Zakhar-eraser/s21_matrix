#include <stdlib.h>

#include "common.h"

void s21_remove_matrix(matrix_t *A) {
  free(A->matrix);
  A->matrix = S21_NULL;
  A->columns = 0;
  A->rows = 0;
}