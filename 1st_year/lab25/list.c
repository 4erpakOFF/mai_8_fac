#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"


bool is_empty(list *l){
  return (l->begin == NULL);
}

list* create(){
  list* temp = malloc(sizeof(list));
  temp->begin = NULL;
  temp->len = 0;
  return temp;
}

void destroy(list* l){
  if (l == NULL) {
    return;
  }
  element* temp = l->begin;
  element* temp1;
  while (temp != NULL){
    temp1 = temp;
    temp = temp->next;
    free(temp1);
  }
  free(l);
}

void destroy_iter(iter* it){
  free(it);
}

int get_len(list* l){
  return l->len;
}

void move_next(iter* it){
  it->prev = it->cur;
  it->cur = it->cur->next;
}

bool insert(iter* it, double v){
  element* new_el = malloc(sizeof(iter));
  if (new_el == NULL)
    return false;
  new_el->val = v;
  new_el->next = it->cur;
  if (it->prev == NULL){
    it->l->begin = new_el;
  } else {
    it->prev->next = new_el;
  }
  it->prev = new_el;
  it->l->len++;
  return true;
}

void delete_el(iter* it){
  element* next = it->cur->next;
  free(it->cur);
  if (it->prev != NULL){
    it->prev->next = next;
  } else{
    it->l->begin = next;
  }
  it->cur = next;
  it->l->len--;
}

bool is_at_end(iter* it){
  return it->cur == NULL;
}

iter* begin_iter(list* l){
  iter* it = malloc(sizeof(iter));
  it->l = l;
  it->cur = l->begin;
  it->prev = NULL;
  return it;
}

void move_prev(iter* it){
  iter* temp_it = malloc(sizeof(iter));
  temp_it->l = it->l;
  temp_it->cur = it->l->begin;
  temp_it->prev = NULL;
  while (temp_it->cur != it->prev){
    move_next(temp_it);
  }
  it->cur = temp_it->cur;
  it->prev = temp_it->prev;
}

double get_val(iter* it){
  return it->cur->val;
}

void set_val(iter* it, double v){
  it->cur->val = v;
}

void list_print(list *l){
  iter *it = begin_iter(l);
  while (!is_at_end(it)){
    printf("%.1lf ", get_val(it));
    move_next(it);
  }
  printf("\n");
  destroy_iter(it);
}

list * list_read(){
  double v;
  list *l = create();
  iter *it = begin_iter(l);
  int n;
  printf("Введите количество элементов списка, а затем и сами элементы\n");
  scanf("%d", &n);
  for (int i = 0; i < n; ++i){
    scanf("%lf", &v);
    insert(it, v);
  }
  destroy_iter(it);
  return l;
}
