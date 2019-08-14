#ifndef VECTOR_H
#define VECTOR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char** str;
    size_t size;
}vector;

vector* vec_create( );
void vec_destroy(vector*);
size_t vec_get_size(vector*);
char* vec_get(vector*, size_t i);
void vec_set(vector*, size_t i, char* str);
void vec_set_size( vector*, size_t);

#endif

