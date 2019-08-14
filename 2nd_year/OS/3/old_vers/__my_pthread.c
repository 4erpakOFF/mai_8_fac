#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "my_pthread.h"


void* thread_search(void* thread_data){
    pthrData* Data = (pthrData*)thread_data;
    tn* t = *(Data->root);
    int* val = Data->s_val;
    if (t->val == *val){    // если есть совпадение
	//printf("Найдено совпадение\n");
	pthread_mutex_lock(&mutex);  // залочим и увеличим число совпадений
	*(Data->sum) = *(Data->sum) + 1;
	pthread_mutex_unlock(&mutex); // разлочим
    }
    /*  
    // Поиск в брате
    if(t->bro != NULL){
	pthread_t thread_bro; // идентификатор потока
	pthrData* broData = (pthrData*)malloc(sizeof(pthrData));
	broData->s_val = val;
	broData->sum = Data->sum;
	broData->root = &(t->bro);

	int tmp = pthread_create(&thread_bro, NULL, thread_search, (void*)broData );//запуск потока
	if( tmp != 0 )
	    printf("Не удалось провести поиск в брате элемента %d\n", t->val );
	else
	    pthread_join(thread_bro, NULL);
	free(broData);
    }
    */ 
    // Поиск в сыне
    if(t->son != NULL){
	pthread_t thread_son;
	pthrData* sonData = (pthrData*)malloc(sizeof(pthrData));
	sonData->s_val = val;
	sonData->sum = Data->sum;
	sonData->root = &(t->son);

	int tmp = pthread_create(&thread_son, NULL, thread_search, (void*)sonData);
	if( tmp != 0 )
	    printf("Не удалось провести поиск в сыне элемента %d\n", t->val );
	else
	    pthread_join(thread_son, NULL);
	free(sonData);
    }
  
    return NULL;
}
