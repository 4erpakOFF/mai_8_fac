#include <stdio.h>

int ABC(int x){
  if((x>='a' && x<='z') || (x>='A' && x<='Z') || x=='-' ){
    return 1;
  } else return 0;
}

int dig(int x){
  if( x>='0' && x<='9' ){
    return 1;
  } else return 0;
}



int main(){
  int c=0, n=0, st=0, no_sep=0;
  
  do{
    c=getchar();
    no_sep=1;

    switch(st){
    case 0:
      if(c>='1' && c<='5'){
	st=1;
      }else if(c=='6'){
	st=6;
      }else if(c>='7' && c<='9'){
	st=2;
      }else if( ABC(c) ){
	st=10;
      }else {
	st=0;
	if(c=='\n'){
	  printf("%d\n", n);
	  n=0;
	  no_sep=0;
	}
      }
      break;

    case 1:
      if( dig(c) ){
	st=2;
      }else if( ABC(c) ){
	st=10;
	if(c=='-'){
	  n++;
	}
      }else {
	n++;
	st=0;
	if(c=='\n'){
	  printf("%d\n",n);
	  n=0;
	  no_sep=0;
	}
      }
      break;

    case 2:
      if( dig(c) ){
	st=3;
      }else if( ABC(c) ){
	st=10;
	if(c=='-'){
	  n++;
	}
      }else {
	n++;
	st=0;
	if(c=='\n'){
	  printf("%d\n",n);
	  n=0;
	  no_sep=0;
	}
      }
      break;

    case 3:
      if( dig(c) ){
	st=4;
      }else if( ABC(c) ){
	st=10;
	if(c=='-'){
	  n++;
	}
      }else {
	n++;
	st=0;
	if(c=='\n'){
	  printf("%d\n",n);
	  n=0;
	  no_sep=0;
	}
      }
      break;
      
    case 4:
      if( dig(c) ){
	st=5;
      }else if( ABC(c) ){
	st=10;
	if(c=='-'){
	  n++;
	}
      }else {
	n++;
	st=0;
	if(c=='\n'){
	  printf("%d\n",n);
	  n=0;
	  no_sep=0;
	}
      }
      break;
      
    case 5:
      if( ABC(c) || dig(c) ){
	st=10;
	if(c=='-'){
	  n++;
	}
      }else {
	n++;
	st=0;
	if(c=='\n'){
	  printf("%d\n",n);
	  n=0;
	  no_sep=0;
	}
      }
      break;

    case 6:
      if(c=='5'){
	st=7;
      }else if(c>='0' && c<='4'){
	st=2;
      }else if(c>='6' && c<='9'){
	st=3;
      }else if( ABC(c) ){
	st=10;
	if(c=='-'){
	  n++;
	}
      }else {
	n++;
	st=0;
	if(c=='\n'){
	  printf("%d\n", n);
	  n=0;
	  no_sep=0;
	}
      }
      break;

    case 7:
      if(c=='5'){
	st=8;
      }else if(c>='0' && c<='4'){
	st=3;
      }else if(c>='6' && c<='9'){
	st=4;
      }else if( ABC(c) ){
	st=10;
	if(c=='-'){
	  n++;
	}
      }else {
	n++;
	st=0;
	if(c=='\n'){
	  printf("%d\n", n);
	  n=0;
	  no_sep=0;
	}
      }
      break;

    case 8:
      if(c=='3'){
	st=9;
      }else if(c>='0' && c<='4'){
	st=4;
      }else if(c>='6' && c<='9'){
	st=5;
      }else if( ABC(c) ){
	st=10;
	if(c=='-'){
	  n++;
	}
      }else {
	n++;
	st=0;
	if(c=='\n'){
	  printf("%d\n", n);
	  n=0;
	  no_sep=0;
	}
      }
      break;

      case 9:
	if(c>='0' && c<='5'){
	  st=5;
	}else if( (c>='6' && c<='9') || ABC(c) ){
	  st=10;
	  if(c=='-'){
	    n++;
	  }
	}else {
	  n++;
	  st=0;
	  if(c=='\n'){
	    printf("%d\n", n);
	    n=0;
	    no_sep=0;
	  }
	}
	break;
	
      case 10:
	if( ABC(c) || dig(c) || c=='-' ){
	  st=10;
	}else {
	  st=0;
	  if(c=='\n'){
	    printf("%d\n", n);
	    n=0;
	    no_sep=0;
	  }
	}
	break;
	
    }                                 // Конец switch'a

    
  }while(c!=EOF);
  if(no_sep){
    printf("\n%d\n", n);
  }
  return 0;
}
