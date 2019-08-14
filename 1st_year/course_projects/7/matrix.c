#include "matrix.h"
#include "vector.h"
#include <stdio.h>

matrix* create_matrix(){
  matrix* m = malloc(sizeof(matrix));
  vector* str = vec_create();
  vector* val = vec_create();
  m->str = str;
  m->val = val;
  m->M = 0;
  m->N = 0;
  return m;
}

matrix* read_matrix(){
  matrix* m = create_matrix();
  int M, N;
  printf("Введите размеры матрицы(кол-во строк и кол-во столбцов через пробел) и сами элеметы матрицы:\n");
  scanf("%d", &M);
  scanf("%d", &N);
  m->M = M;
  m->N = N;
  if(M==0 || N==0) return m;
  for(int i=0; i<M; i++){
    vec_push_back(m->str, vec_get_size(m->val)/2);
    for(int j=0; j<N; j++){
      int tmp;
      scanf("%d", &tmp);
      if(tmp){
	vec_push_back(m->val, j);
	vec_push_back(m->val, tmp);
      }
    }
  }
  vec_push_back(m->str, vec_get_size(m->val)/2);
  return m;
}

void print_matrix(matrix *m){
  for(int i=0; i < m->M; i++){
    int index = vec_get(m->str, i) * 2;
    int end = vec_get(m->str, i+1) * 2;
    for(int j=0; j < m->N; j++){
      if(index==end){
	printf("0 ");
	continue;
      }
      if(j==vec_get(m->val,index)){
	printf("%d ", vec_get(m->val, index+1) );
	index+=2;
      }else printf("0 ");
    }
    printf("\n");
  }
  printf("\n");
}

vector* read_vector(matrix* m){
  vector* vec = vec_create();
  int N = m->N;
  printf("Введите элементы столбца (размерностью %d), на который хотите домножить матрицу:\n",N);
  for(int i=0; i<N; i++){
    int tmp;
    scanf("%d", &tmp);
    vec_push_back(vec, tmp);
  }
  return vec;
}

void print_vector(vector* vec){
  for( int i=0; i<vec_get_size(vec); i++) printf("%d ", vec_get(vec, i) );
  //printf("\n");
}

vector* multiply(matrix* m, vector* vec){
  vector* output = vec_create();
  for(int i =0; i<vec_get_size(m->str); i++){
    int index = vec_get(m->str, i) * 2;
    int end = vec_get(m->str, i+1) * 2;
    int tmp=0;
    for( int i=index; i<=end; i+=2){
      if(i==end){
	vec_push_back(output,tmp);
	break;
      }
      tmp += vec_get(m->val,i+1)*vec_get(vec, vec_get(m->val, i) );
    }
  }
  return output;
}

int non_zero(vector* vec){
  int count=0;
  for( int i=0; i < vec_get_size(vec); i++){
    if( vec_get(vec, i) ) count++;
  }
  return count;
}

void free_matrix(matrix* m){
  vec_destroy(m->str);
  vec_destroy(m->val);
  free(m);
}

