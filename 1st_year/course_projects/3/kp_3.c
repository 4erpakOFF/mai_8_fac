#include <stdio.h>
#include <math.h>

long double calc_eps(){
  long  double res=1;
  while(res+1!=1){
    res/=2;
  }
  return res*2;
}

long double ld_abs(long double x){
  if(x>0){
    return x;
  }else{
    return -x;
  }
}
/*___________Вариант 12___________*/

int main(){
  
  const long  double eps = calc_eps(), a=0.0, b=1.0;
  int n;
  scanf("%d", &n);
  
  printf("\nМашинное эпсилон для типа double = %Le\n\n", eps);
  printf("     Таблица значений ряда Тейлора и стандартной функции для f(x) = 3^x\n");
  printf(" +--------------+--------------+--------------+---------------+----------+\n");
  printf(" |   Значение   |   Частичная  |   Значение   |  Погрешность  |   Число  |\n |      X       |  cумма  ряда |    функции   |               | итераций |\n");
  printf(" +--------------+--------------+--------------+---------------+----------+\n");

  
  long double step = (b-a)/n, x=a, delta=0;;
  long double taylor=1, orig=1, taylor_part=1;
  int iters = 1;
  for(int i=0; i<n+1; i++){
    while(ld_abs(taylor_part) >= eps  && iters <= 100){
      if(x!=0){
	taylor_part = taylor_part*( (log(3)*x)/iters);
	taylor += taylor_part;
	iters++;
      }else{
	break;
      }
    }
    orig =  pow(3.0, x);
    delta = orig - taylor;
    
    printf(" | %Le | %Le | %Le | %13Le | %08d |\n", x, taylor, orig, delta, iters);
    x+=step;
    iters=1;
    taylor=1;
    orig=1;
    taylor_part = 1;
  }

  printf(" +--------------+--------------+--------------+---------------+----------+\n");
  return 0;
}
