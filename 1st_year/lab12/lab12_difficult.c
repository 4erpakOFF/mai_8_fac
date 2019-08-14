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
  int a,_a, res = 0;

  while(1==scanf("%d", &a)){

    int A[10] = {0};
    int check = 1;
    _a = a;

    for(a=a; a!=0; a=a/10){
      res = _a%10;
      _a = a;
      
      for(int i=0; i<=9; ++i){
	if ( abs(res) == i){ A[i] = 1;
	}
      }
    }
    res =_a%10;
    for(int i=0; i<=9; ++i){
      if (abs(res) == i){ A[i] = 1;
      }
    }
    for(int i=0;i<=9; ++i){
      if(A[i]==0){
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
	
	else{
	  A[i]=0;
	}
      }
      printf("\n"); 
    }
    else {
      printf("Каждая цифра встречается как минимум 1 раз\n");
    }
    
  }
 

}

