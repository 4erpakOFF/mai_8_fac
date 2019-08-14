#ifndef __PASSENGERS_h__
#define __PASSENGERS_h__

typedef struct{
  char surname[30];
  char initials[4];
  int sum_things;
  double weight_things;
  char destination[30];
  char time[5];
  int transfer;
  int child;
}passenger;

#endif
