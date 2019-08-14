// вариант 20
// Вектор, строки длиной от 0 до 255.

#include <stdio.h>
#include "vector.h"

int main(int argc, char* argv[]) {
	vector* v = vec_create();

	vec_set_size(v, 1);
	vec_set(v, 0, "The ting goes skrrrahh");
	printf("%s\n", vec_get(v, 0));

	vec_set_size(v, 5);
	for (size_t i = 0; i < 5; ++i)	
		vec_set(v, i, "pap");
	for (size_t i = 0; i < 5; i++) 
		printf("%s ", vec_get(v, i));
	printf("\n");

	vec_destroy(v);
	return 0;
}
