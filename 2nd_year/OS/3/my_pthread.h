#ifndef MY_PTRHEAD
#define MY_PTRHEAD

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "my_pthread.h"


typedef struct search_args pthrData;
struct search_args{
    tn** root;
    int* s_val;   // search val
    //int path;
    int* sum;  // ссылка на общее число вхождений
};


pthread_mutex_t mutex;
void* thread_search(void* thread_data);



#endif
