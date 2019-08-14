/* 
   Щербаков А.А.
   Вариант 9: сортировка 2х файлов и их слияние"
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#define _STR_SIZE_ 500
#define _NUM_OF_STR_ 100
#define _RESULT_ "result"

int file_to_str(FILE* file, char strings[_NUM_OF_STR_][_STR_SIZE_]){
    int count = 0;
    while( fgets( strings[count], _STR_SIZE_, file)!=NULL && count < _NUM_OF_STR_)
        ++count;
    return count;
}


// Сортирвка пузырьком для строк
void str_bubble_sort(char strings[_NUM_OF_STR_][_STR_SIZE_], int size){
    int i = 0, j = 0;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1; j++) {
            if ( strcmp(strings[j], strings[j+1]) >0) {  // >0,если первая строка больше
                char tmp[_STR_SIZE_] = " ";
                strcpy(tmp, strings[j]);
                strcpy(strings[j], strings[j+1]);      //strings[j] = strings[j+1];
                strcpy(strings[j+1], tmp);
            }
        }
    }
}


void write_to_file(char strings[_NUM_OF_STR_][_STR_SIZE_], int fd_result){   //   (массив строк для записи, файловый дескриптор файла)
    for(int i=0; i < _NUM_OF_STR_; ++i){
        int length = strlen( strings[i] );
        if( length <= 0 ) break;
        if (write(fd_result, &(strings[i]), length) <= 0){
            printf("Ошибка записи первого отсортированного файлаn\n");
            break;
        }
    }
}

int sort_and_write_to_pipe(char* file_name, int fd[2]){   // (сортируемый файл, файловые дескрипторы пайпа)
    close( fd[0] );
    FILE* file = fopen(file_name, "r");
    if (file == NULL){
        printf("Файл %s не найден\n", file_name);
        return -1 ;
    }
    char strings[_NUM_OF_STR_][_STR_SIZE_];
    int size = file_to_str(file, strings);
    fclose(file);
    if( size == 0 ) return -1;

    str_bubble_sort(strings, size);
    if( write(fd[1], strings, _STR_SIZE_*size ) <= 0 ){
        printf("Ошибка передачи первого отсортированного файла\n");
        return -1;
    }
    close( fd[1] );
    return 0;
}

//--------------- MAIN -----------------------------------------

int main(int argc, char *argv[]){
    int fd_1[2], fd_2[2];
    pid_t child_1, child_2;
    char *name_1, *name_2, buf[100];
    char sep[10] = " \n";


    if( pipe(fd_1)<0 || pipe(fd_2)<0 ){   // pipe
        perror("pipe");
        exit(-1);
    }

    printf("Введите имена двух файлов\n");
    if( fgets(buf, 50, stdin) == NULL ){  // fgets
        printf("Не удалось считать имена файлов\n");
        exit(-1);
    }

    name_1 = strtok(buf, sep);  //имя первого файла
    name_2 = strtok(NULL, sep); //имя второго файла
    if(name_1 == NULL || name_2 == NULL){
        printf("Не указаны имена двух файлов\n");
        exit(-1);
    }

    //name_1 = "1.txt";
    //name_2 = "2.txt";

    if( ( child_1=fork() ) == 0 )                        // I дочерний
        exit( sort_and_write_to_pipe(name_1, fd_1 ) );

    if( ( child_2 = fork() ) == 0 )                      // II дочерний
        exit( sort_and_write_to_pipe(name_2, fd_2) );
    //------------------------------------------------

    if( child_1 < 0 || child_2 < 0 ){               //проверяем детей
        perror("fork");
        exit(-1);
    }

    if (child_1 > 0 && child_2 > 0){                  // Родительский
        close(fd_1[1]);
        close(fd_2[1]);
        int fd_result = creat(_RESULT_, S_IRWXU); //владелец файла имеет права на чтение, запись и выполнение файла
        int exit_status;
        char sorted_strings_1[_NUM_OF_STR_][_STR_SIZE_], sorted_strings_2[_NUM_OF_STR_][_STR_SIZE_];
        if( fd_result < 0 ){
            printf("Не удается создать файл для записи\n");
            perror(_RESULT_);
            exit(-1);
        }
        waitpid(child_1, &exit_status, 0);
        if( WEXITSTATUS(exit_status) == 0 ){
            if( read(fd_1[0], &sorted_strings_1, _STR_SIZE_*_NUM_OF_STR_) <= 0 )
                printf("Ошибка чтения первого отсортированного файла\n");
            else
                write_to_file(sorted_strings_1, fd_result);
        }
        waitpid(child_2, &exit_status, 0);
        if( WEXITSTATUS(exit_status) == 0 ){
            if( read(fd_2[0], sorted_strings_2, _STR_SIZE_*_NUM_OF_STR_) <= 0 )
                printf("Ошибка чтения второго отсортированнго файла\n");
            else
                write_to_file( sorted_strings_2, fd_result);
        }
        close(fd_result);
    }
    close(fd_1[0]);
    close(fd_2[0]);
    return 0;
}
