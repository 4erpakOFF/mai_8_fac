#include <stdio.h>
#define size 100
// Вариант 11

int main(){
  int arr[size][size] = {0};
  int max, st=1, i, j;
  
  printf("Введите сначала ПОРЯДОК матрицы, не превышающий %d, а затем  -  ЭЛЕМЕНТЫ матрицы.\n", size);
  scanf("%d", &max);
  max--;
  for(int x=0; x<=max; x++){
    for(int y=0; y<=max; y++){
      scanf("%d", &arr[x][y]);
    }
  }
  i = max;
  j = max;
  while(st){ 
    switch(st){
    case 1:
      while(i<=max && j>=0){
	printf("%d ", arr[i][j]);
	i++;
	j--;
      }
      i--;
      j++;
      st=2;
      if(j>0){
	j--;
      }else if(i>0){
	i--;
      }else {
	st=0;
      }
      break;
      
    case 2:
      while(i>=0 && j<=max){
	printf("%d ", arr[i][j]);
	i--;
	j++;
      }
      i++;
      j--;
      st=1;
      if(i>0){
	i--;
      }else if(j>0){
	j--;
      }else {
	st=0;
      }
      break;
      
    }          // end of switch
  }
  printf("\n");
  return 0;
}

  
