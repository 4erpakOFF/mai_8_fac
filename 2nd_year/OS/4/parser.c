#include "parser.h"

#define _PATH_ 20

void skip() {
	char c;
	while ((c = getchar()) != '\n') {}
	return;
}

void ERROR() {
	printf("ERROR: Неопознанная команда. Введите \\help для отображения списка команд\n");
	return;
}

void help() {
	if (fork() == 0) {
		execl("/bin/cat", "cat", "help", NULL);
	}
	wait(NULL);
	return;
}

void parser() {
	char c;
	char pattern[20];
	//char substit[20];
	char command[10];
	char path[_PATH_];
	FILE* file = NULL, * newfile = NULL;
	size_t f_size = 0;
	while (true) {
		printf("Введите имя файла:  ");
		scanf("%s", path);
		skip();
		if ((file = fopen(path, "r+")) == NULL)
			printf("Файл %s не наден \n", path);
		else {
			if (is_already_opened(path, true)) {     // Защита от открытия в нескольких процессах
				printf("Файл %s уже используется другим процессом\n", path);
				fclose(file);
			}
			else {
				printf("Файл %s успешно открыт\n", path);
				f_size = file_size(file);
				break;
			}
		}
	}
	printf("'%s' >>> ", path);
	while ((c = getchar()) != EOF) {
		if (c == '\\') {
			if ((c = getchar()) != ' ' && c != '\n' && c != '\t') {
				ungetc(c, stdin);
				scanf("%s", command);
				if (strcmp(command, "help") == 0) {
					help();
				}
				else if (strcmp(command, "exit") == 0) {
					break;
				}
				else if (strcmp(command, "search") == 0) {  //search
					scanf("%s", pattern);
					search(file, f_size, pattern);
				}
				else if (strcmp(command, "erase") == 0) {   //erase
					int position, count;
					int check = scanf("%d%d", &position, &count);
					if (check == 2) {
						erase(file, position, count);
					}
					else {
						printf("Неверный формат данных (помощь: '\\help')\n");
						continue;
					}
				}
				else if (strcmp(command, "write") == 0) { //write_to_file
					char text[30];
					int position;
					int check = scanf("%d%s", &position, text);
					if (check == 2) {
						write_to_file(file, position, text);
					}
					else {
						printf("Неверный формат данных команды (помощь: '\\help')\n");
						continue;
					}

				}
				else if (strcmp(command, "range") == 0) {
					range(file, f_size);
				}
				else if (strcmp(command, "open") == 0) {
					char newpath[_PATH_];
					scanf("%s", newpath);
					if ((newfile = fopen(newpath, "r+")) == NULL) {
						printf("Файл %s не найден\n", newpath);
						fclose(newfile);
					}
					else {
						if (is_already_opened(newpath, true)) {
							printf("Файл %s уже используется другим процессом\n", newpath);
							fclose(newfile);
						}
						else {
							fclose(file);
							file = newfile;
							strcpy(path, newpath);
							printf("Файл %s открыт успешно\n", path);
							f_size = file_size(file);
						}
					}
				}
				else if (strcmp(command, "print") == 0) {
					print_file(path);
				}
				else {
					ERROR();
				}
				if (c != '\n') skip();
			}
			else {
				ERROR();
				if (c != '\n') skip();
			}
		}
		else {
			ERROR();
			if (c != '\n') skip();
		}
		printf("'%s' >>> ", path);
	}
	fclose(file);
}
