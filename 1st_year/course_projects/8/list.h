#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

typedef struct element element;
struct element {
  double val;
  element* next;
};

typedef struct {
  int len;
  element* begin;
} list;

typedef struct {
  list* l;
  element* prev;
  element* cur;
} iter;

bool is_empty(list *);
list* create();
void destroy(list* l);
void destroy_iter(iter* it);
int get_len(list* l);
void move_next(iter* it);
bool insert(iter* it, double v);
void delete_el(iter* it);
bool is_at_end(iter* it);
bool is_at_begin(iter* it);
iter* begin_iter(list* l);
void move_prev(iter* it);
double get_val(iter* it);
void set_val(iter* it, double v);

#endif
