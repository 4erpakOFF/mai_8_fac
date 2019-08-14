#include <stdio.h>
#include "insert_sort.h"

// Линейный список;
// Процедура: вставка элемента в упорядоченный
//               по возр. список с сохранением порядка
// Метод: сортировка простой вставкой


int main(){
  list *l = list_read();
  insert_sort(l);
  printf("----------\nОтсортированный список:\n");
  list_print(l);
  return 0;
}

