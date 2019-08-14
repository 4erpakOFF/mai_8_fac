#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "insert_sort.h"

void insert_to_sorted( list* l, double a){
  iter* it = begin_iter(l);
  list* Greater = create();
  iter* it_G = begin_iter(Greater);
  bool is_added = false;
  while( !is_empty(l) ){
    double e = get_val(it);
    delete_el(it);
    if(!is_added && e>a ){
      insert(it_G, a);
      is_added=true;
    }
    insert(it_G, e);
  }
  if(!is_added) insert(it_G, a);
  destroy_iter(it_G);
  it_G = begin_iter(Greater);
  
  while( it_G->cur->next != NULL){
    insert( it, get_val(it_G) );
    move_next(it_G);
  }
  if(!is_at_end(it_G) ) insert( it, get_val(it_G) );
  destroy_iter(it_G);
  destroy_iter(it);
  destroy(Greater);
  return;
}


void insert_sort(list* l){
  iter* it = begin_iter(l);
  double val;
  if( get_len(l) > 1){
    val = get_val(it);
    delete_el(it);
    insert_sort(l);
    insert_to_sorted(l, val);
  }else return;
}
   
