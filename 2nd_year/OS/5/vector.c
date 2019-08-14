#include "vector.h"

vector* vec_create() {
	vector* v = (vector*)malloc(sizeof(vector));
	if (v != NULL) {
		v->size = 0;
		v->str = NULL;
	}
	return v;
}

void vec_destroy(vector* v) {
	size_t size = vec_get_size(v);
	for (size_t i = 0; i < size; ++i) free(v->str[i]);
	free(v->str);
	free(v);
}

size_t vec_get_size(vector* v) {
	return v->size;
}

char* vec_get(vector* v, size_t i) {
	return v->str[i];
}

void vec_set(vector* v, size_t i, char* str) {
	v->str[i] = realloc(v->str[i], sizeof(char) * strlen(str));
	strcpy(v->str[i], str);
}


void vec_set_size(vector* v, size_t s) {
	char** tmp = (char**)realloc(v->str, s * sizeof(char*));
	if (tmp != NULL) {
		for (size_t i = v->size; i < s; i++) tmp[i] = NULL;
		v->str = tmp;
		v->size = s;
	}
	else printf("Не удалось изменить размер вектора\n");
	return;
}
