#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"


tn* tn_create(int val) {
	tn* root = (tn*)malloc(sizeof(tn));
	root->val = val;
	root->son = NULL;
	root->bro = NULL;
	return root;
}

bool is_sep(char a) {
	return (a == ' ' || a == '\t' || a == '\n' || a == '\0');
}

void tn_add(tn** root, char* cmd) {
	char a[_STR_LEN_];
	strcpy(a, cmd);
	tn* t = *root;
	int val = 0;
	char sep[5] = " \t\n\0";
	char* plus, * c_val, * paths;

	plus = strtok(a, sep); // +
	c_val = strtok(NULL, sep); // val
	paths = strtok(NULL, sep); // путь или пути

	//printf("%s %s %s\n", plus, c_val, paths);   //просто проверка

	if (strcmp(plus, "+") != 0 || c_val == NULL || (c_val[0] != '-' && (c_val[0] < '0' || c_val[0] > '9') && c_val[0] != '+') || paths == NULL) {
		printf("Неверно введены данные для заполнения дерева: %s\n", cmd);
		return;
	}
	val = atoi(c_val);
	// больше не нужны, поэтому будем использовать их для дальнейших разбиений

	// то что далее, потом в цикл, если нужно 
	t = *root;
	if (strcmp(paths, "/") == 0) {  // если paths == '/'
		if (t == NULL) {
			*root = tn_create(val);
			t = *root;
		}
		else {
			while (t->bro != NULL) t = t->bro;
			t->bro = tn_create(val);
		}


	}
	else {
		char* path_c_val, * path_rest = paths;
		char* path_sep = "/";
		int path_val;
		while (path_rest != NULL) {
			path_c_val = strtok(path_rest, path_sep);
			path_rest = strtok(NULL, sep);

			/* // Для проверки:
			   if(path_rest != NULL) printf("%s   %s\n", path_c_val, path_rest);
			   else printf("NULL\n");
			*/

			if (path_c_val == NULL || (path_c_val[0] != '-' && (path_c_val[0]<'0' || path_c_val[0]>'9'))) {
				printf("Неверно указан путь %s\n", paths);
				break;
			}
			path_val = atoi(path_c_val); // значение сына, которого мы должны искать

			if (t->val != path_val) {        // весь if для того, чтобы добраться до path_val
				bool is_path_right = true;
				while (t->val != path_val) {
					if (t->bro != NULL) t = t->bro;
					else {
						printf(" Нет пути %s\n", paths);
						is_path_right = false;
						break;
					}
				}
				if (!is_path_right) break;  // если нет пути, то не нужно дальше его разбирать
			}

			if (t->son == NULL) {
				if (path_rest == NULL)   // если мы в конце пути, то можно создать сына.
					t->son = tn_create(val);
				else
					printf("Нет пути %s\n", paths);
			}
			else {
				t = t->son;
				if (path_rest == NULL) {
					while (t->bro != NULL) t = t->bro;
					t->bro = tn_create(val);
				}
			}
		} // конец разбора 1 пути
	} // конец else для разбора 1 пути


	return;
}

void tn_print(tn* t, int level) {
	if (t != NULL) {
		for (int i = 0; i < level; i++) printf("  ");
		printf("%d\n", t->val);
		tn_print(t->son, level + 1);
		tn_print(t->bro, level);
	}
	else; // do nothing
}

void tn_destroy(tn* t) {
	if (t == NULL) return;
	tn_destroy(t->bro);
	tn_destroy(t->son);
	free(t);
}

