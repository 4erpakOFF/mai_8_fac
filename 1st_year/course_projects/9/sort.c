#include "sort.h"

void swap(double *a, double *b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

void Shellsort(TABLE* tab){
  int step, n = tab->size;
  for(step=n/2; step>0; step/=2){
    for(int i=step; i<n; i++){
      for(int j=i; j>=step; j-=step){
	if(tab->key[i] < tab->key[j-step]){
	  swap(&tab->data[i], &tab->data[j-step]);
	  swap(&tab->key[i], &tab->key[j-step]);
	}else break;
      }
    }
  }
}
  

int binary_search(TABLE* tab, double val){
  double* arr = tab->key;
  int n = tab->size;
  int left=0, right=n-1, middle;
  while(left<=right){
    middle = (left + right)/2;
    if(val <= arr[middle]) {
      right = middle - 1;
    }else if(val > arr[middle]) {
      left = middle + 1;
    }
  }
  if (arr[left] == val)  return left;
  return -1;
}

