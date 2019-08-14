#include <stdio.h>
#define max 8

// Вариант 12


int main(){
  int N[max*max]={0};
  int a, all_size=0, size=-1, displace=0;

  printf("\n      Циклический сдвиг массива по спирали против часовой стрелки\n\nВведите сначала  ЧИСЛО элементов, на которое необходимо выполнить сдвиг,\nа затем -  ЭЛЕМЕНТЫ квадратной матрицы (порядок не более %d)\n", max);

  scanf("%d", &displace);
  while( 1==scanf("%d", &a) ){
    N[all_size] = a;
    all_size++;
  }
 
  for(int i=1; i<=max; i++){
    if( i*i == all_size ){
      size = i;
      break;
    }
  }
  if(size==-1){
    printf("\nМатрица не удовлетворяет условию\n");
  }else{
  //-------------------------------------------------------
    displace %= all_size;
    if(displace<0){
      displace = -displace;
    }else if(displace > 0){
      displace = all_size - displace;
    }
    
    for(int z=0; z<displace; z++){
      int m=0,x=0, st=0, sz=size, cache = N[0];
      int dist_bottom=sz-1, dist_right=sz-1;
      
      for(int i=0; i<all_size; i++){
	switch(st){
	case 0:
	  if(dist_bottom>0){
	    m+=size;
	    dist_bottom--;
	  }else if(dist_right>0){
	    m++;
	    dist_right--;
	  }else {                                         
	    sz--;
	    st=1;
	    m-=size;
	  }
	  break;
	  
	case 1:
	  if(sz-1-dist_bottom>0){
	    m-=size;
	    dist_bottom++;
	  }else if(sz-1-dist_right>0){
	    m--;
	    dist_right++;
	  }else {
	    sz--;
	    st=0;
	    m+=size;
	    dist_bottom=sz-1;
	    dist_right=sz-1;
	  }
	  break;
	}
	
	if(i==all_size-1){
	  N[x] = cache;
	}else{
	  N[x]= N[m];
	  x=m;
	}
      }
    }
    //----------------------------------------------------
    
    printf("\nОтвет:\n\n");
    for(int i=0; i<all_size; i++){
      printf(" %d", N[i]);
      if((i+1)%size==0){
	printf("\n");
      }
    }
  }
    printf("\n");
  return 0;
}

