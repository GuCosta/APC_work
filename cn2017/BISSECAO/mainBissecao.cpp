#include <stdio.h>
#include <math.h>
#include <iostream>
#include "bissecao.h"
using namespace std;
inline double func_1(double x);
inline double func_2(double x);
int main(){
	Bissecao obj;
	double tmp;
	int er;
	printf("Digite a precisao (modulo do expoente do 10).\n");
	cin >> er;
	obj.set_err(er);
	obj.set_precision();
	printf("Funcao :: x^3 + 3*x + 1\n");
	obj.intervalos(func_2);
	obj.bissecao(func_2);
	return 0;
}


inline double func_1(double x){return (pow(x,3) + 30*pow(x,2) + 2552);}

inline double func_2(double x){return (pow(x,3) + 3*x + 1);}












