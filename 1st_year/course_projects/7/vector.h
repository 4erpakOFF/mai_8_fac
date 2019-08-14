#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>

typedef struct {
  int* body;
  int size;
} vector;

vector* vec_create();
void vec_destroy(vector*);
int vec_get_size(vector*);
int vec_get(vector*, int);
void vec_set(vector*, int, int);
void vec_push_back(vector*, int);
#endif
