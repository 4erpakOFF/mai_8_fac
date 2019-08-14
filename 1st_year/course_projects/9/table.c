#include <stdio.h>
#include <stdlib.h>
#include "table.h"

void table_read(TABLE* tab) {
  printf("Введите размер таблицы: ");
  scanf("%d", &tab->size);
  if (tab->size == 0) {
    return;
  }
  tab->data = malloc(tab->size * sizeof(double));
  tab->key = malloc(tab->size * sizeof(double));
  printf("Введите попарно ключи и элементы:\n");
  for (int i = 0; i < tab->size; ++i) {
    scanf("%lf %lf", &tab->key[i], &tab->data[i]);
  }
}

void table_print(TABLE *tab) {
  for (int i = 0; i < tab->size; ++i) {
    printf("%.2lf %.2lf\n", tab->key[i], tab->data[i]);
  }
}
