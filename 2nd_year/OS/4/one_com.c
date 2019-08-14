#include "one_com.h"

void Usage() {
	if (fork() == 0)
		execl("/bin/cat", "cat", "usage", NULL);
	wait(NULL);
	return;
}

void OC_ERROR() {
	printf("Неопознанная команда\n");
	if (fork() == 0)
		execl("/bin/cat", "cat", "help");
	wait(NULL);
}

void one_com(int argc, char** args) {
	char c;
	char command[20];
	char word[10];
	char path[20];
	char* arg1, * arg2;
	FILE* file = NULL, * newfile = NULL;
	size_t f_size = 0;


	/*                  Разбор имени                    */

	printf("%s\n", args[1]);
	if (args[1][0] != '/') {
		Usage();
		return;
	}
	size_t i = 0;
	size_t shift = 1;
	while ((c = args[1][i + shift]) != ':' && c != ' ' && c != '\t' && c != '\n' && c != EOF) {
		word[i] = c;
		++i;
	}
	word[i] = '\0';
	if (c != ':' || strcmp(word, "file") != 0) {
		Usage();
		return;
	}

	shift += i + 1;
	i = 0;
	while ((c = args[1][i + shift]) != '\0') {
		path[i] = c;
		++i;
	}
	path[i] = '\0';
	printf("File: %s\n", path);

	if (is_already_opened(path, false)) {
		printf("Файл %s уже используется другим процессом\n", path);
		return;
	}
	if ((file = fopen(path, "r+")) == NULL) {
		printf("Файл %s не найден\n", path);
		return;
	}
	f_size = file_size(file);


	/*                       Разбор команд                     */


	for (size_t j = 2; j < argc; ++j) {
		printf("%s\n", args[j]);
		if (args[j][0] != '/') {
			Usage();
			return;
		}
		size_t i = 0;
		size_t shift = 1;
		// printf("ОПА\n");
		while ((c = args[j][i + shift]) != ':' && c != ' ' && c != '\t' && c != '\n' && c != EOF) {
			word[i] = c;
			++i;
		}
		word[i] = '\0';
		if (c != ':' || strcmp(word, "command")) {
			Usage();
			return;
		}

		shift += i + 1;
		i = 0;
		while ((c = args[j][i + shift]) != '\0' && c != ':') {
			command[i] = c;
			++i;
		}
		command[i] = '\0';
		printf("~%s~\n", command);


		/*           Пытаемся выполнить задание          */


		if (strcmp(command, "range") == 0) {    //range
			range(file, f_size);
		}
		else if (strcmp(command, "exit") == 0) {    //exit
			break;
		}
		else if (strcmp(command, "search") == 0) {  //search
			if (argc - j < 1) {
				printf("ERROR: команда 'search' требует наличия 1 аргумента!\n");
				return;
			}
			arg1 = args[++j];
			search(file, f_size, arg1);
		}
		else if (strcmp(command, "open") == 0) {  // open
			if (argc - j < 1) {
				printf("ERROR: команда 'open' требует наличия 1 аргумента!\n");
				return;
			}
			arg1 = args[++j];
			if ((newfile = fopen(arg1, "r+")) == NULL) {
				printf("Файл %s не найден\n", arg1);
				fclose(newfile);
			}
			else {
				if (is_already_opened(arg1, true)) {
					printf("Файл %s Уже используется другим процессом\n", arg1);
					fclose(newfile);
				}
				else {
					fclose(file);
					file = newfile;
					strcpy(path, arg1);
					printf("Файл %s открыт успешно\n", path);
				}
			}
		}
		else if (strcmp(command, "print") == 0) {  //print
			print_file(path);

		}
		else if (strcmp(command, "erase") == 0) {   // erase
			if (argc - j < 2) {
				printf("ERROR: команда 'erase' требует наличия 2x аргументов!\n");
				return;
			}
			arg1 = args[++j];
			arg2 = args[++j];

			erase(file, atoi(arg1), atoi(arg2));
		}
		else if (strcmp(command, "write") == 0) {  // write
			if (argc - j < 2) {
				printf("ERROR: команда 'write' требует наличия 2x аргументов!\n");
				return;
			}
			arg1 = args[++j];
			arg2 = args[++j];

			write_to_file(file, atoi(arg1), arg2);
		}
		else {
			OC_ERROR();
		}
	}  // for( j=2, j<args, ++j)
}
