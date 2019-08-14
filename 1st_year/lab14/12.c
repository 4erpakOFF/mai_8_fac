#include <stdio.h>
#define size 100
// Вариант 12

int main(){
  int arr[size][size] = {0};
  int max, st=1, i=0, j=0;
  
  printf("Введите сначала ПОРЯДОК матрицы, не превышающий %d, а затем  -  ЭЛЕМЕНТЫ матрицы.\n", size);
  scanf("%d", &max);
  max--;
  for(int x=0; x<=max; x++){
    for(int y=0; y<=max; y++){
      scanf("%d", &arr[x][y]);
    }
  }
  
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
      if(i<max){
	i++;
      }else if(j<max){
	j++;
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
      if(j<max){
	j++;
      }else if(i<max){
	i++;
      }else {
	st=0;
      }
      break;
      
    }          // end of switch
  }
  printf("\n");
  return 0;
}

  
