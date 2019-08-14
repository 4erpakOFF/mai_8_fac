#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"

typedef struct{
  vector* str;
  vector* val;
  int M;
  int N;
}matrix;

matrix* create_matrix();
matrix* read_matrix();
void print_matrix(matrix*);
vector* read_vector(matrix*);
void print_vector(vector*);
vector* multiply(matrix*, vector*);
int non_zero(vector*);
void free_matrix(matrix*);

#endif
