#include <stdio.h>
#define size 100
// Вариант 13

int main(){
  int arr[size][size] = {0};
  int max, st=1, i, j, count=0;
  
  printf("Введите сначала ПОРЯДОК матрицы, не превышающий %d, а затем  -  ЭЛЕМЕНТЫ матрицы.\n", size);
  scanf("%d", &max);
  max--;

  for(int x=0; x<=max; x++){
    for(int y=0; y<=max; y++){
      scanf("%d", &arr[x][y]);
    }
  }

  i=0;
  j=max;
  
  while(st){ 
    switch(st){
      
    case 1:
      while(i<=max && j>=0){
	printf("%d ", arr[i][j]);
	i++;
	j--;
	count++;
      }
      i--;
      j++;
      if( count==(max+1)*(max+1)){
	st=0;
      }else if(j==0){
	i--;
	st=2;
      }else if(i==max) {
	i = max-i;
	j = max-j;
      }
      break;

    case 2:
       while(i>=0 && j<=max){
	printf("%d ", arr[i][j]);
	i--;
	j++;
	count++;
      }
      i++;
      j--;
      if(count==(max+1)*(max+1)){
	st=0;
      }else if(j==max){
	i++;
	st=1;
      }else if(i==0) {
	i = max-i;
	j = max-j;
      }
      break;

    }
  }
  printf("\n");
  return 0;
}

      
