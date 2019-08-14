#include <stdio.h>
#include <math.h>

double calc_eps() {                                   // Нахожднеие машинного эпсилон
	double res = 1;
	while (res + 1 != 1) {
		res /= 2;
	}
	return res * 2;
}
double d_abs(double x) {                               // Модуль для типа double
	if (x >= 0) {
		return x;
	}
	else {
		return -x;
	}
}
double df(double F(), double x) {                       // Функция ищет первую производную
	double h = 1e-7;
	return (F(x + h) - F(x - h)) / (2 * h);
}

double df_2(double F(), double x) {                    //Функция ищет вторую производную
	double h = 1e-7;
	return (F(x + h) + F(x - h) - F(x) * 2) / (h*h);
}

//12
// log(x) - x + 1.8; отрезок [2;3]
// Приблженное значение корня: 2.8459
double F_12(double x) {                                  // Исходная функция F(x)
	return log(x) - x + 1.8;
}
double f_12(double x) {                                  // x = f(x)
	return log(x) + 1.8;
}

//13
// x*tg(x)-1/3; отрезок [0.2 ; 1.0]
// Приблженное значение корня: 0.5472

double F_13(double x) {                                  // Исходная функция F(x)
	return (x*tan(x) - 1.0 / 3.0);
}
double f_13(double x) {                                  // x = f(x)
	return (x - x * tan(x) + 1.0 / 3.0);
}


double dihotomia(double F(), double a, double b, double eps, char* err_d)
{
	if (F(a)*F(b) < 0) {
		while (d_abs(a - b) > 2 * eps) {
			if (F(a)*F((a + b) / 2) > 0) {
				a = (a + b) / 2;
			}
			else if (F(b)*F((a + b) / 2) > 0) {
				b = (a + b) / 2;
			}
			else {
				if (F(a) == 0) {
					return a;
				}
				else if (F(b) == 0) {
					return b;
				}
				else {
					*err_d = 99;
					return 0;
				}
			}
		}
		return (a + b) / 2;
	}
	else {
		*err_d = 1;
		return 0;
	}
}


double iters(double F(), double f(), double begin, double end, double eps, char *err_i)
{
	double x = (begin + end) / 2;
	double _x = 0, f_1;
	while (d_abs(x - _x) > 2 * eps) {
		f_1 = df(f, x);
		if (d_abs(f_1) < 1) {
			if (x > begin && x < end) {
				_x = x;
				x = f(x);
			}
			else {
				*err_i = 1;
				return 0;
			}
		}
		else {
			*err_i = 2;
			return 0;
		}
	}
	return x;
}

double newton(double F(), double a, double b, double eps, char *err_n)
{
	double x = (b + a) / 2;
	double _x = 0, F_1, F_2;
	while (d_abs(x - _x) > 2 * eps) {
		F_1 = df(F, x);
		F_2 = df_2(F, x);
		if (d_abs(F(x)*F_2) < F_1*F_1) {
			if (x > a && x < b) {
				_x = x;
				x = x - F(x) / F_1;
			}
			else {
				*err_n = 1;
				return 0;
			}
		}
		else {
			*err_n = 2;
			return 0;
		}
	}
	return x;
}


int main() {
	char err_i = 0, err_n = 0, err_d = 0;
	double a, b, eps = calc_eps(), result_d, result_i, result_n;
	int st = 0;
	printf("  \nВыберите нужный вариант (12 или 13) и введите отрезок:\n\n 12) log(x)-x+1.8, рекомендуемый отрезок [2;3];\n 13) x*tg(x)-1/3,рекомендуемый отрезок [0.2; 1.0]\n");
	scanf("%d%le%le", &st, &a, &b);
	if (st == 12 || st == 13) {
		switch (st) {
		case 12:
			result_d = dihotomia(F_12, a, b, eps, &err_d);
			result_i = iters(F_12, f_12, a, b, eps, &err_i);
			result_n = newton(F_12, a, b, eps, &err_n);
			break;


		case 13:
			result_d = dihotomia(F_13, a, b, eps, &err_d);
			result_i = iters(F_13, f_13, a, b, eps, &err_i);
			result_n = newton(F_13, a, b, eps, &err_n);
			break;

		}

		printf(" Метод дихтомии: ");
		if (err_d == 1) {
			printf("ошибка 1\n");
		}
		else if (err_d == 99) {
			printf("неизвестная ошибка\n");
		}
		else {
			printf("%le\n", result_d);
		}

		printf(" Метод итераций: ");
		if (err_i == 1) {
			printf("ошибка 1\n");
		}
		else if (err_i == 2) {
			printf("ошибка 2\n");
		}
		else {
			printf("%le\n", result_i);
		}

		printf(" Метод Ньютона:  ");
		if (err_n == 1) {
			printf("ошибка 1\n");
		}
		else if (err_n == 2) {
			printf("ошибка 2\n");
		}
		else {
			printf("%le\n", result_n);
		}

	}
	else {
		printf("Вы выбрали несуществующий вариант\n");
	}
	return 0;
}

