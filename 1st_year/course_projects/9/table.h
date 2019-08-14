#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
  double* data;
  double* key;
  int size;
} TABLE;

void table_read(TABLE*);
void table_print(TABLE*);

#endif
