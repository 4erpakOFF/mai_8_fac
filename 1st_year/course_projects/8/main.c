#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"
#include <stdbool.h>

#define _ERR_ 1
#define _MANY_ '+'
#define _EMPTY_ printf("!  Список пуст\n")

void new_comand(){
  printf("Введите новую команду:\n");
}
bool is_sep(int c){
  return ( c==' ' || c=='\n' || c=='\t' || c==EOF);
}
int skip_sep(int c){
  while( is_sep(c) ){
    if(c=='\n') return c;
    c=getchar();
  }
  return c;
}



int main(){
  new_comand();
  bool is_need_get_char;
  list* l = create();
  double v;
  int c = getchar(), st=0;
  iter* it = begin_iter(l);
  do{
    is_need_get_char = true;
    //c = skip_sep(c);
    switch(st){
    case 0:
      if( is_sep(c) ) break;
      if(c=='h') st= 'h';        //help
      else if(c=='d') st= 'd';   //delete current
      else if(c=='c') st= 'c';   //clean
      else if(c=='p') st= 'p';   //print
      else if(c=='t') st= 't';   //task :Если найдем введенный пользователем элемент, то очистить список
      else if(c=='q') st= 'q';   //quit
      else if(c=='m') st= 'm';   //move
      else if(c=='s') st= 's';   //set
      else if(c=='i') st= 'i';   //insert
      else if(c=='g') st= 'g';   //get
      else if(c==';') st=';';    // end of input
      else st= _ERR_;            //error
	
      break;

      
      //----------HELP----------
    case 'h':
      printf("   Я бы рад помочь, не времени нет ;(\nПридется открывать код и смотреть там\n");
      st=0;
      new_comand();
      break;
      
      //----------INSERT----------
    case 'i':
      while(1==scanf("%lf", &v)){
	insert(it, v);
      }
      c=getchar();
      if(c!=';') is_need_get_char=false;
      st=0;
      new_comand();
      break;
  
      
      //----------DELETE----------
    case 'd':                               
      if(is_empty(l)){
	printf("!  Список и без того уже пуст\n");
      }else if( is_at_end(it) ){
	printf("!  Нельзя удалить несуществующий элемент\n");
      }else{
	delete_el(it);
      }
      new_comand();
      st=0;
      break;

      
      //---------PRINT----------
    case 'p':
      {
	printf("----------\n");
	iter* it1 = begin_iter(l);
	long int cnt = 1;
	if (is_empty(it->l)) {
	  _EMPTY_;
	}else{
	  while (!is_at_end(it1)) {
	    printf("%ld: %.2lf", cnt++, get_val(it1));
	    if (it->cur == it1->cur) {
	      printf(" <==");
	    }
	    printf("\n");
	    move_next(it1);
	  }
	  if (is_at_end(it) ) printf("   <==\n");
	  destroy_iter(it1);
	}
	printf("----------\n");
	st=0;
	new_comand();
	break;
      }

      
      //----------MOVE---------------
    case 'm':
      {
	//int step=1;
	//c=getchar();
	if(c!='n' && c!='p' && c!='b' && c!='e'){
	  st=_ERR_;
	  break;
	}
	if(is_empty(l) ){
	  _EMPTY_;
	}else{
	  if( c=='n'){                        //Next
	    if( is_at_end(it) ) printf("!  Вы находитесь в конце списка\n");
	    else move_next(it);

	    
	  }else if( c=='p' ){                     // Previos
	    if(is_at_begin(it) ) printf("!  Вы находитесь в начале списка\n");
	    else move_prev(it);
	    
	  }else if(c=='b'){
	    if(is_at_begin(it) ) printf("!  Вы уже находитесь в начале списка\n");
	    else
	      while( !is_at_begin(it) ) move_prev(it);
	    
	  }else if(c=='e'){
	    if( is_at_end(it) ) printf("!  Вы уже находитесь в конце списка\n");
	    else
	      while( !is_at_end(it) ) move_next(it);
	  }
	}
	st=0;
	new_comand();
	break;
      }
      
      //----------CLEAN--------------
    case 'c':
      if( is_empty(l) ) _EMPTY_;
      else{
	while( !is_at_begin(it) ) move_prev(it);
	while( !is_at_end(it)   ) delete_el(it);
	printf("!  Список очищен\n");
      }
      st=0;
      new_comand();
      break;


      //------GET VALUE---------------
    case 'g':
      if(is_at_end(it) ) printf("!  Вы находитесь в конце списка\n");
      else printf("!  Значение текущего элемента равно %lf\n", get_val(it) );
      st=0;
      new_comand();
      break;


      //------------SET VALUE----------

    case 's':
      {
	double val;
	printf("Введите число, на которое следует заменить значение текущего элемента:\n");
	if(scanf("%lf", &val)==1){
	  if(is_empty(l)) _EMPTY_;
	  else if(is_at_end(it)) printf("!  Вы находитесь в конце списка\n");
	  else{
	    set_val(it, val);
	    printf("!  Значение текущего элемента изменено\n");
	  }
	}else printf("!  Не было введено числа\n");
	st=0;
	new_comand();
	break;
      }
	
	
      
      //--------------TASK-------------
    case 't':
      {
	printf("Введите элемент для поиска:\n");
	double val;
	if(scanf("%lf", &val)==1){
	  if (is_empty(l)){
	    printf("-----\n");
	    _EMPTY_;
	    printf("-----\n");  
	  }else{
	    iter* it1=begin_iter(l);
	    while(!is_at_end(it1)){
	      if( val==get_val(it1) ){
		while( !is_at_begin(it) ) move_prev(it);
		while( !is_at_end(it)   ) delete_el(it);
		printf("-----\nНайдено совпадение => список очищен\n-----\n");
		break;
	      }
	      if(is_at_end(it1)){
		printf("-----\nСовпадений не найдено => список очищен не был\n-----\n");
		break;
	      }
	      move_next(it1);
	    }
	    destroy_iter(it1);
	  }
	}else
	  printf("!  Не было введено числа для поиска\n");
	st=0;
	new_comand();
	break;
      }
	    
	      
      //------------END OF INPUT-----------------
    case ';':
      st=0;
      break;

      
      //----------------ERROR----------------
    case _ERR_:
      printf("!!!Error!!! Некорректная команда. Для просмотра доступных команд введите 'h' \n");
      while( !is_sep(c) ) c=getchar();
      st=0;
      break;

    case 'q':
      return 0;

      
    }
    if(is_need_get_char) c=getchar();
  }while(c!=EOF); 
  return 0;
}
