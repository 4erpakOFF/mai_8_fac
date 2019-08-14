#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
	const int Length_1 = 11, Length_2 = 9, Skip_1 = 5, Skip_2 = 6;
	int length = Length_1 + Length_2;
	char buf[32];
	int fd_write, fd_read;
	char* file_read = "read.txt", * file_write = "write.txt";


	if ((fd_write = creat(file_write, S_IRUSR | S_IWUSR)) < 0) {
		perror(file_read);
		exit(1);
	}
	if ((fd_read = open(file_read, O_RDONLY)) < 0) {
		perror(file_write);
		exit(1);
	}

	lseek(fd_read, Skip_1, SEEK_SET);
	if (read(fd_read, buf, Length_1) <= 0) {
		printf("Ошибка чтения на 1 этапе!\n");
		exit(-1);
	}
	lseek(fd_read, Skip_2, SEEK_CUR);
	if (read(fd_read, &buf[Length_1], Length_2) <= 0) {
		printf("Ошибка чтения на 2 этапе!\n");
		exit(-1);
	}

	buf[length] = '\0';
	printf("Содержимое буффера: \n");
	write(1, buf, length + 1);

	printf("-----------\nЗапись в файл %s \t", file_write);
	if (write(fd_write, buf, length) <= 0)
		printf("Ошибка записи\n");
	else
		printf("Успешно\n");

	close(fd_write);
	close(fd_read);

	int id = 0;
	if ((id = fork()) == 0) {
		printf("Содержимое файла \"write.txt\" :\n");
		execl("/bin/cat", "cat", "write.txt", NULL);
		printf("\n");
		exit(0);
	}

	waitpid(id, NULL, 0);

	return 0;
}
