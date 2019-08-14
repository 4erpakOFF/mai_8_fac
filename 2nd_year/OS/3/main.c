//  Вариант 7

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "tree.h"
#include "my_pthread.h"



int main(int argc, char* argv[]) {
	tn* root = NULL;

	//------------------------ начало заполнения дерева
	char buf[_STR_LEN_];
	if (argc < 2) {
		printf("Не указан файл, хранящий данные о дереве\n");
		return 0;
	}
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		perror("Ошибка открытия файла");
		return 1;
	}

	while (!feof(file)) {
		memset(buf, '\0', sizeof(buf));
		fgets(buf, _STR_LEN_, file);
		if (buf[0] == '\0') break;
		tn_add(&root, buf);
		//printf("-------\n");
	}

	if (root == NULL) {
		printf("Дерево пусто\n");
		return 0;
	}
	tn_print(root, 0);
	//------------------------------ конец заполнения дерева


	int s_val = 0; // то, что будем искать
	printf("Подавайте на вход числа, которые нужно найти:\n");
	int check;
	while ((check = scanf("%d", &s_val)) != EOF) {
		if (check == 0) break;
		int sum = 0;
		// int s_val = 0;  // элемент, который нужно найти
		pthrData* Data = (pthrData*)malloc(sizeof(pthrData));
		Data->root = &root;
		Data->s_val = &s_val;
		Data->sum = &sum;

		pthread_t thread; // дескриптор потока
		pthread_mutex_init(&mutex, NULL);  //инициализация мьютекса

		// запускаем поток:
		pthread_create(&thread, NULL, thread_search, (void*)Data);
		pthread_join(thread, NULL); // ждем завершения

		pthread_mutex_destroy(&mutex);  // уничтожение мьютекса
		free(Data);

		printf(" Количество вхождений числа %d: %d\n", s_val, sum);
	}
	tn_destroy(root);
	return 0;
}
