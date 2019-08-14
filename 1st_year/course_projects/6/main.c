#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "passenger.h"

//------Вариант 32-------

int main(int argc, char* argv[]){
  double p;
  passenger pass;
  if(argc == 2)  p=0;  // По умолчанию параметр будет равен нулю
  else if(argc==3) p=atoi(argv[2]);
  else{
    fprintf(stderr, "ERROR! Неверное число аргументов\n");
    return 1;
  }
  //------------------------------
  FILE* bin = fopen(argv[1], "r");
  if(bin==NULL){
    perror("Невозможно открыть файл");
    return 2;
  }
  int count=0;
  double max_weight=0;
  while(fread(&pass, sizeof(passenger), 1, bin)==1){       
    if(pass.weight_things > max_weight) max_weight = pass.weight_things;
    if(pass.sum_things > 0) count++;
  }
  if(count==0){
    printf("Нет пассажиров\n");
    return 0;
  }else if(max_weight==0){
    printf("Пасажиры не перевозят вещей\n");
    return 0;
  }else{
    printf("Максимальный вес: %.3lf\n", max_weight);
    printf("Пользовательский параметр: %.3lf\n\n", p);
  }
  count=0;
  fseek(bin, 0, SEEK_SET);
  while(fread(&pass, sizeof(passenger), 1, bin)==1){
    count++;
    if(max_weight-p <= pass.weight_things){
      printf("%d) %s %s  Вес груза: %.3lf\n", count, pass.surname, pass.initials, pass.weight_things);
    }
  }
  fclose(bin);
  return 0;
}
