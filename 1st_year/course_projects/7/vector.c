#include "vector.h"

vector* vec_create() {
  vector* a = malloc(sizeof(vector));
  a->body = NULL;
  a->size = 0;
  return a;
}

void vec_destroy(vector* a) {
  free(a->body);
  free(a);
}

int vec_get_size(vector* a) {
  return a->size;
}

int vec_get(vector* a, int i) {
  if (i >= 0 && i < a->size){
    return a->body[i];
  }
  return -1;
}

void vec_set(vector* a, int i, int v) {
  if (i >= 0 && i < a->size) a->body[i] = v;
}

void vec_push_back(vector* a, int v) {
  a->body = realloc(a->body, (1 + a->size) * sizeof(int));
  a->body[a->size] = v;
  a->size++;
}

