#include <stdio.h>

int abs(int j){
  if(j>=0){
    return j;  
  }
  else {
    return -j;
  }
}

int main(){
  int a, q, res = 0;

  while(1==scanf("%d", &a)){
    
    int A[10] = {0};
    int check = 1;

    do{
      res = a%10;
      a = a/10;
      q = abs(res);
      A[q] = 1;
    } while(a!=0);
    
    for(int i=0;i<=9; ++i){
      if(A[i] == 0){
	check = 0;
	break;
      }
    }
    
    if(check == 0){
      printf("Ни разу не встречаются цифры:");
      for(int i=0; i<=9; i++){
	if(A[i]==0){
	  printf(" %d ", i);
	}
      }
      printf("\n\n"); 
    }
    else{
      printf("Каждая цифра встречается как минимум 1 раз\n\n");
    }

  }


}

