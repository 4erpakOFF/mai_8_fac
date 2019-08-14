#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "passenger.h"

int main(int argc, char* argv[]){   //args: 1 - database.txt, 2 - dump.bin
  if( argc!= 3){
    if(argc<3) fprintf(stderr, "Недостаточное количество аргументов\n");
    if(argc>3) fprintf(stderr, "Слишком большое количество аргументов\n");
    return 1;
  }
  passenger p;
  FILE* input = fopen(argv[1],"r"); // Считывание database.txt
  FILE* output = fopen(argv[2], "w"); //запись в бинарник
  if(input==NULL){
    perror("Неозможно открыть файл для считывания данных");
    return 2;
  }else if(output==NULL){
    perror("Невозможно открыть файл для записи данных");
    return 2;
  }
  int n=0;
  while(fscanf(input,"%[^:]:%[^:]:%d:%lf:%[^:]:%[^:]:%d:%d", p.surname, p.initials, &p.sum_things, &p.weight_things, p.destination, p.time, &p.transfer, &p.child)==8){
    fscanf(input, "\n");
    // printf("%s\n", p.surname);
    fwrite(&p, sizeof(passenger), 1, output);
    n++;
  }
  printf("Количество элементов базы данных равно %d\n", n);
  fclose(input);
  fclose(output);
  return 0;
}
