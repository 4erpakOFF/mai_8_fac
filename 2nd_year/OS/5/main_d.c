// вариант 20
// Вектор, строки длиной от 0 до 255.

#include <stdio.h>
#include "vector.h"
#include <dlfcn.h>

int main(int argc, char* argv[]) {
	vector* (*vec_create)();
	void (*vec_destroy)(vector*);
	size_t(*vec_get_size)(vector*);
	char* (*vec_get)(vector*, size_t i);
	void (*vec_set)(vector*, size_t i, char* str);
	void (*vec_set_size)(vector*, size_t);

	void* lib = dlopen("libvector.so", RTLD_LAZY);
	if (!lib) {
		fprintf(stderr, "dlopen() ERROR: %s\n", dlerror());
		return 1;
	}

	vec_create = dlsym(lib, "vec_create");
	vec_destroy = dlsym(lib, "vec_destroy");
	vec_get_size = dlsym(lib, "vec_get_size");
	vec_get = dlsym(lib, "vec_get");
	vec_set = dlsym(lib, "vec_set");
	vec_set_size = dlsym(lib, "vec_set_size");


	char* error;
	if (error = dlerror()) {
		printf("%s\n", error);
		return 1;
	}


	vector* v = (*vec_create)();

	(*vec_set_size)(v, 1);
	(*vec_set)(v, 0, "The ting goes skrrrahh");
	printf("%s\n", (*vec_get)(v, 0));

	(*vec_set_size)(v, 5);
	for (size_t i = 0; i < 5; ++i)	
		(*vec_set)(v, i, "pap");
	for (size_t i = 0; i < 5; i++) 
		printf("%s ", (*vec_get)(v, i));
	printf("\n");

	(*vec_destroy)(v);

	dlclose(lib);
}
