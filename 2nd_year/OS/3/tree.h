#ifndef TREE_H
#define TREE_H
#include <stdbool.h>

#define _STR_LEN_ 50

typedef struct tn tn;
struct tn{
    int val;
    tn *son;
    tn* bro;
};

tn *tn_create(int val);
void tn_add(tn** root, char* command);
void tn_print(tn* root, int level);
void tn_destroy(tn* t);


#endif
	

  
