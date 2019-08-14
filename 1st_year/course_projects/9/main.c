#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

// Задание: сортировка Шелла

int main() {
  TABLE* tab = malloc(sizeof(TABLE));
  if (tab != NULL) {
    table_read(tab);
    Shellsort(tab);
    printf("-----------\nОтсортированная таблица:\n");
    table_print(tab);
    printf("\nВведите ключ для поиска элемента: ");
    double k;
    while(1==scanf("%lf", &k) ){
      int res = binary_search(tab, k);
      if(res != -1) printf("Индекс первого вхождения: %d\n", res);
      else printf("Нет элементов с заданным ключом.\n");
      printf("\nВведите ключ для поиска элемента: ");
    }
  }
  free(tab);
}

