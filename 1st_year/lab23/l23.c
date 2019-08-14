#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//____________Вариант 12

#define _ERR_ 1
#define _TASK_ is_tn_a_list(t)

typedef struct tn tn;
struct tn{
  double val;
  tn* l;
  tn* r;
};

bool tn_add(tn** t, double val){
  if(*t==NULL){
    tn* tmp = (tn*)malloc(sizeof(tn));
    tmp->l = NULL;
    tmp->r = NULL;
    tmp->val = val;
    if(tmp==NULL){
      return false;
    }else{
      *t=tmp;
      return true;
    }
  }else if(val < (*t)->val){
    return tn_add( &(*t)->l, val);
  }else if(val > (*t)->val){
    return tn_add( &(*t)->r, val);
  }else if(val == (*t)->val){
    return true;
  }else return false;
}

void tn_del(tn** t){
  if( (*t)!=NULL){
    tn* tmp = *t;
    if( (*t)->l == NULL ){
      (*t) = (*t)->r;
    }else if( (*t)->r == NULL ){
      (*t) = (*t)->l;
    }else{
      tn** change = &(*t)->l;
      if( (*change)->r!=NULL){
	while( (*change)->r != NULL) change = &(*change)->r;
	tn* l_child = (*change)->l;
	(*change)->l = (*t)->l;
	(*change)->r = (*t)->r;
	(*t) = (*change);
	(*change) = l_child;
      }else{
	(*change)->r = (*t)->r;
	(*t) = (*change);
      }
    }
    free(tmp);
  }else ; //do nothing
}

void tn_clean(tn** t){
  if ( (*t)->l !=NULL) tn_clean( &(*t)->l);
  if ( (*t)->r !=NULL) tn_clean( &(*t)->r);
  tn_del(t);
}
  
void tn_print(tn* t, int level){
  if( t!=NULL){
    tn_print( t->r, level+1 );
    for(int i=0; i<level; i++) printf("  ");
    printf("-<%lf\n", t->val);
    tn_print( t->l, level+1);
  }else ; //do nothing
}

bool is_tn_a_lin_list(tn* t){
  if( t==NULL ){
    return false;
  }else if( t->l!=NULL ){
    while( t->l!=NULL ){
      if( t->r!=NULL) return false;
      t= t->l;
    }
  }else if( t->r!=NULL ){
    while( t->r!=NULL){
      if( t->l!=NULL) return false;
      t= t->r;
    }
  }
  return true;
}

bool is_tn_a_list(tn* t){
  if( t==NULL) return false;
  if( t->r!=NULL && t->l==NULL) return is_tn_a_list( t->r);
  if( t->l!=NULL && t->r==NULL) return is_tn_a_list( t->l);
  if( t->r==NULL && t->l==NULL) return true;
  return false;
}
      
tn** tn_search(tn** t, double val){
  if( (*t)==NULL || val==(*t)->val) return t;
  if(val> (*t)->val) return tn_search( &(*t)->r, val);
  if(val< (*t)->val) return tn_search( &(*t)->l, val);
  return NULL;
 }

bool is_sep(int c){
  return ( c==' ' || c=='\n' || c=='\t' || c==EOF);
}
int skip_args(int c){
  while( is_sep(c) || (c>='0' && c<='9') ){
    if(c=='\n') return c;
    c = getchar();
  }
  return c;
}
void help(){
  printf("Программа для работы с бинарными деревьями.\n");
  printf("  Перечень команд:\n");
  printf("+-------------------------------------------------------------------------------+\n");
  printf("| Команда (Сокращения)       --         Описание                                |\n");
  printf("+-------------------------------------------------------------------------------+\n");
  printf("| help    (h)                -- справка по доступным комнадам;                  |\n");
  printf("| add     (a)      [arglist] -- добавление узлов дерева;                        |\n");
  printf("| delete  (del, d) [arglist] -- удаление узла дерева;                           |\n");
  printf("| clean   (c)                -- Удаление всех узлов дерева;                     |\n");
  printf("| end     (e)                -- конец ввода;                                    |\n");
  printf("| print   (p)                -- печать дерева;                                  |\n");
  printf("| task    (t)                -- является ли дерево линейным списком(вариант 12);|\n");
  printf("| quit    (q)                -- выход из программы;                             |\n");
  printf("+-------------------------------------------------------------------------------+\n");
  printf("!!! Программа допускает ввод нескольких команд в одну строку, но будьте внимательны при вводе !!!\n\n");
}
//---------------------------------------------------

int main(){
  tn* t=NULL;
  double val;
  int c='\n', st=0;
  bool is_correct=true; //Переменная для проверки введенных команд
  bool is_need = false;
  bool is_args_skip = false;
  
  help();
  printf("INPUT> ");
  do{
    if(!is_args_skip) c=getchar();
    else is_args_skip = false;
    is_need = true;
    switch(st){
    case 0:
      if(c>='0' && c<='9'){
	printf("!!!Error!!! Встречены аргументы без подходящей команды\n");
	c = skip_args(c);
	is_need = false;
	is_args_skip = true;
	break;
      }
      if( is_sep(c) ){
	if( c== '\n'){
	  printf("INPUT> ");
	  is_need=false;
	}
	is_need=false;
	break;
      }
      is_need=false;
      //  if( is_sep(c) ) break;
      if(c=='h') st= 'h';        //help
      else if(c=='a') st= 'a';   //add
      else if(c=='d') st= 'd';   //delete
      else if(c=='c') st= 'c';   //clean
      else if(c=='e') st= 'e';   //end (of input)
      else if(c=='p') st= 'p';   //print
      else if(c=='t') st= 't';   //task
      else if(c=='q') st= 'q';   //quit
      else st= _ERR_;            //error
      break;

      
      //----------HELP----------
    case 'h':
      is_correct=false;
      if( is_sep(c) ) is_correct=true;
      else if(c=='e'){
	c=getchar();
	if(c=='l'){
	  c=getchar();
	  if(c=='p'){
	    c=getchar();
	    if( is_sep(c) ) is_correct=true;
	  }
	}
      }
      if(is_correct){
	printf("\n");
	help();
	st=0;
      }else{
	st = _ERR_;
      }
      break;
      
      //----------ADD----------
    case 'a':                                      
      is_correct=false;
      if( is_sep(c) ) is_correct=true;
      else if(c=='d'){
	c=getchar();
	if(c=='d'){
	  c=getchar();
	  if( is_sep(c) ) is_correct=true;
	}
      }
      if(is_correct){
	int is_func_correct=-1;
	while( scanf("%lf", &val) == 1){
	  is_func_correct = tn_add(&t, val);
	  if(!is_func_correct){
	    printf("<ADD> : !!!ERROR!!! Возникла ошибка при добавлении элементов, начиная с числа %le\n", val);
	    c = skip_args(c); // Пропустить следующие аргументы
	    is_args_skip = true;
	    break;
	  }
	} 
	if(is_func_correct==1) printf("<ADD> : Done!\n");
	else if(is_func_correct==-1) printf("<ADD> : Не было добавлено ни одного элемента\n");
	st = 0;
      }else{
	st = _ERR_;
      }
      is_need=false;
      break;
      
      //----------DELETE----------
    case 'd':                               
      is_correct=false;
      if( is_sep(c) ) is_correct=true;
      else if(c=='e'){
	c=getchar();
	if(c=='l'){
	  c=getchar();
	  if( is_sep(c) ) is_correct=true;
	  else if(c=='e'){
	    c=getchar();
	    if(c=='t'){
	      c=getchar();
	      if(c=='e'){
		c=getchar();
		if( is_sep(c) ) is_correct=true;
	      }
	    }
	  }
	}
      }
      if( is_correct ){
	while( scanf("%lf", &val)==1)  tn_del( tn_search(&t,val) );
	st=0;
	printf("<DELETE> : Done!\n");
      }else{
	st=_ERR_;
      }
      break;

      //----------CLEAN----------
    case 'c':
      is_correct=false;
      if( is_sep(c) ) is_correct=true;
      else if(c=='l'){
	c=getchar();
	if(c=='e'){
	  c=getchar();
	  if(c=='a'){
	    c=getchar();
	    if(c=='n'){
	      c=getchar();
	      if( is_sep(c) ) is_correct=true;
	    }
	  }
	}
      }
      if( is_correct ){
	tn_clean(&t);
	st=0;
	printf("<CLEAN> : Done!\n");
      }else{
	st=_ERR_;
      }
      break;
      
      //----------END of input---------
    case 'e':
      is_correct = false;
      if( is_sep(c) ) is_correct=true;
      else if(c=='n'){
	c=getchar();
	if(c=='d'){
	  c=getchar();
	  if( is_sep(c) ) is_correct=true;
	}
      }
      if(is_correct){
	printf("Введите новую команду. Для просмотра доступных команд введите 'h' или 'help' \n");
	st=0;
      }else{
	st=_ERR_;
      }
      break;
      
      //---------PRINT----------
    case 'p':
      is_correct=false;
      if( is_sep(c) ) is_correct=true;
      else if(c=='r'){
	c=getchar();
	if(c=='i'){
	  c=getchar();
	  if(c=='n'){
	    c=getchar();
	    if(c=='t'){
	      c=getchar();
	      if( is_sep(c) ) is_correct=true;
	    }
	  }
	}
      }
      if(is_correct){
	printf("<PRINT> : ");
	if( t==NULL){
	  printf("NULL\n");
	}else{
	  printf("\n");
	  tn_print(t, 1);
	}
	st=0;
      }else{
	st=_ERR_;
      }
      break;

      //----------TASK----------
    case 't':
      is_correct=false;
      if( is_sep(c) ) is_correct=true;
      else if(c=='a'){
	c=getchar();
	if(c=='s'){
	  c=getchar();
	  if(c=='k'){
	    c=getchar();
	    if( is_sep(c) ) is_correct=true;
	  }
	}
      }
      if(is_correct){
	printf("<TASK> : ");
	if(_TASK_) printf("true\n");
	else printf("false\n");
	st=0;
      }else{
	st=_ERR_;
      }
      break;
	
      //----------QUIT----------
    case 'q':                                       
      is_correct=false;
      if( is_sep(c) ) is_correct=true;
      else if(c=='u'){
	c=getchar();
	if(c=='i'){
	  c=getchar();
	  if(c=='t'){
	    c=getchar();
	    if( is_sep(c) ) is_correct=true;
	  }
	}
      }
      if(is_correct){
	st=0;
	return 0;
      }else{
	st = _ERR_;
      }
      break;

      //----------ERROR----------
    case _ERR_:
      printf("!!!Error!!! Некорректная команда. Для просмотра доступных команд введите 'h' или 'help' \n");
      while( !is_sep(c) ) c=getchar();
      st=0;
      break;
    }
    if(st==0 && is_need && c=='\n')printf("INPUT> ");
  }while(c!=EOF);
  tn_clean(&t);
  return 0;
}