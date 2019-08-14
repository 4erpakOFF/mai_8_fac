#include "matrix.h"
#include <stdio.h>

int main(){
  int check = 1;
  matrix* m = create_matrix();
  while(check){
    m = read_matrix();
    if(m->M==0 || m->N==0){
      printf("!!!Error: Число строк или столбцов данной матрицы равно 0 => Выпоолнение программы невозможно.\n\nПовторите ввод:\n");
    }else{
      check = 0;
    }
  }
  vector* vec = read_vector(m);
  printf("---------------\n");
  printf("Матрица:\n");
  print_matrix(m);
  
  printf("Столбец:\n");
  printf("( ");
  print_vector(vec);
  printf(")^T\n\n");
  
  vector* result = multiply(m,vec);
  printf("Результат произведения (строка):\n");
  print_vector(result);
  printf("\n\n");

  printf("Количество ненулевых элементов произведения:  %d\n", non_zero(result));
  printf("-------------\n");
  vec_destroy(result);
  vec_destroy(vec);
  free_matrix(m);
  return 0;
}
  
  
