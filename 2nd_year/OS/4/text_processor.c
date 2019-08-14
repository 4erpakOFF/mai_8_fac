#include "text_processor.h"

void print_file(char* path) {
	printf("------------------------------------------\n");
	if (fork() == 0)
		execl("/bin/cat", "cat", path, NULL);
	wait(NULL);
	printf("\n------------------------------------------\n");
	return;
}

size_t file_size(FILE* file) {   // засунем в парсер, чтобы не вычислять каждый раз
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);
	return size;
}

bool is_sep(char c) {
	return (c == ' ' || c == '\n' || c == '\t' || c == '\0');
}

void range(FILE* file, size_t file_size) {
	if (file_size == 0) {
		printf("Файл пуст\n");
		return;
	}
	fseek(file, 0, SEEK_SET);
	char c[1], min = CHAR_MAX, max = CHAR_MIN;
	for (size_t i = 0; i < file_size; ++i) {
		fread(c, sizeof(char), 1, file);
		if (c[0] < min && c[0] > ' ' && !is_sep(c[0])) min = c[0];
		if (c[0] > max && !is_sep(c[0])) max = c[0];
	}
	fseek(file, 0, SEEK_SET);
	printf("Диапазон символов: min =='%c', max == '%c'\n", min, max);
	return;
}

bool is_already_opened(char* path, bool is_from_parser) {
	//int end_size = strlen("lsof  | wc -l") + strlen(path);
	int crutch;
	if (is_from_parser) crutch = 3;
	else crutch = 0;
	int number;
	char command[30];
	command[0] = '\0';

	strcat(command, "lsof ");
	strcat(command, path);
	strcat(command, " | wc -l");
	//strcat(command, " > test");

	FILE* tmp = popen(command, "r");
	fscanf(tmp, "%d", &number);
	pclose(tmp);
	//printf("%s\n", command);
	//printf("число  %d\n", number-crutch);
	if (number - crutch > 1) return true; // вообще без понятия,почему, но на старте выдает 4, отсюда и -3.
	else return false;
}

void search(FILE* file, size_t file_size, char* pattern) {
	size_t patt_size = strlen(pattern);
	size_t count = 0;
	char tmp[patt_size + 1];
	if (file_size <= 0) {
		printf("Файл пуст\n");
		return;
	}
	if (patt_size <= 0) {
		printf("Подстрока для поиска пуста\n");
		return;
	}
	if (file_size < patt_size) {
		printf("Совпадений нет\n");
		return;
	}
	fseek(file, 0, SEEK_SET);
	for (size_t i = 0; i <= file_size - patt_size; ++i) {
		fread(tmp, patt_size, 1, file);
		if (strcmp(tmp, pattern) == 0)
			++count;
		fseek(file, i + 1, SEEK_SET);
	}
	printf("Количество совпадений: %lu\n", count);
}


void erase(FILE* file, int position, int count) {
	if (file == NULL) {
		printf("Файл пуст\n");
		return;
	}
	--position;
	int fd_file = fileno(file);    // получаем файловый дескриптор открытого файла
	lseek(fd_file, position + count, SEEK_SET);
	int fd = open("./", __O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0) {
		printf("Не удается создать временный файл\n");
		return;
	}
	char c;
	while (read(fd_file, &c, 1) == 1) {
		if (write(fd, &c, 1) != 1) {
			printf("Ошибка записи во временный файл\n");
			return;
		}
	}

	if (ftruncate(fd_file, position) < 0) {
		printf("Не удается выполнить удаление с данной позиции\n");
		return;
	}

	lseek(fd_file, position, SEEK_SET);
	lseek(fd, 0, SEEK_SET);
	while (read(fd, &c, 1) == 1) {
		if (write(fd_file, &c, 1) != 1) {
			printf("Не удается записать в исходный файл\n");
			lseek(fd_file, 0, SEEK_SET);
			return;
		}
	}
	lseek(fd_file, 0, SEEK_SET);
}

void write_to_file(FILE* file, int position, char* text) {
	--position;
	int fd_file = fileno(file);
	lseek(fd_file, position, SEEK_SET);
	int fd = open("./", __O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0) {
		printf("Не удается создать временный файл\n");
		return;
	}
	char c;
	while (read(fd_file, &c, 1) == 1) {
		if (write(fd, &c, 1) != 1) {
			printf("Не удается записать во временный файл\n");
			return;
		}
	}

	if (ftruncate(fd_file, position) < 0) {
		printf("Не удается удаление с данной позиции\n");
		return;
	}

	lseek(fd_file, position, SEEK_SET);
	if (write(fd_file, text, strlen(text)) != strlen(text)) {
		printf("Не удается запись в иcходный файл\n");
		lseek(fd_file, position, SEEK_SET);
		return;
	}

	lseek(fd, 0, SEEK_SET);
	while (read(fd, &c, 1) == 1) {
		if (write(fd_file, &c, 1) != 1) {
			printf("Не удается запись в исходный файл\n");
			return;
		}
	}
	lseek(fd_file, 0, SEEK_SET);
	return;
}


