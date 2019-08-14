//  Вариант 7

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "tree.h"
//#define _STR_LEN_ 50
#define _MAX_THREAD_ 20

pthread_mutex_t mutex;

typedef struct search_args pthrData;
struct search_args{
    tn** root;
    int* s_val;   // search val
    //int path;
    int* sum;  // ссылка на общее число вхождений
};

void* thread_search(void* thread_data){
    pthrData* Data = (pthrData*)thread_data;
    tn* t = *(Data->root);
    int* val = Data->s_val;
    if (t->val == *val){    // если есть совпадение
	printf("Найдено совпадение\n");
	pthread_mutex_lock(&mutex);  // залочим и увеличим число совпадений
	*(Data->sum) = *(Data->sum) + 1;
	pthread_mutex_unlock(&mutex); // разлочим
    }
  
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






int main(int argc, char* argv[]){
    tn* root = NULL;

    //------------------------ начало заполнения дерева
    char buf[_STR_LEN_];
    if(argc < 0){
	printf("Не указан файл, хранящий данные о дереве\n");
	return 0;
    }
    FILE* file = fopen("test_", "r");
    if(file == NULL){
	perror("Ошибка открытия файла");
	return 1;
    }

    while( !feof(file) ){
	memset(buf, '\0', sizeof(buf) );
	fgets(buf, _STR_LEN_, file);
	if ( buf[0] == '\0' ) break;
	tn_add(&root, buf);
	//printf("-------\n");
    }
    tn_print(root, 0);
    //------------------------------ конец заполнения дерева
  
    int sum = 0;
    int s_val = 3;  // элемент, который нужно найти
    pthrData* Data = (pthrData*)malloc(sizeof(pthrData));
    Data->root = &root;
    Data->s_val = &s_val;
    Data->sum = &sum;

    pthread_t thread; // дескриптор потока
    pthread_mutex_init(&mutex, NULL);  //инициализация мьютекса
  
    // запускаем поток:
    pthread_create( &thread, NULL, thread_search, (void*)Data );
    pthread_join(thread, NULL);
    pthread_mutex_destroy(&mutex);  // уничтожение мьютекса
    free(Data);

    printf("Количество совпадений: %d\n", sum);
    tn_destroy(root);
    return 0;
}
