#include <stdio.h>
#include <math.h>
#include <iostream>
#include "pontofixo.h"
using namespace std;
inline double func_1(double x);
int main(){
	PontoFixo obj;
	double x0;
	int err;
	printf("Digite a precisao (modulo do expoente do 10).\n");
	cin >> err;
	printf("Digite x0 : \n");
	cin >> x0;

	obj.set_err(err);
	obj.set_x0(x0);
	obj.set_precision();

	printf("Funcao :: x^3 - 30x^2 + 2552\n");
	obj.pontofixo(x0,func_1, 100);		//ateh 100 iterracoes
	return 0;
}

inline double func_1(double x){return (pow(x,3) - 30*pow(x,2) + 2552);}