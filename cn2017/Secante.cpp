#include <stdio.h>
#include <math.h>
#include <iostream>
#include "secante.h"
using namespace std;
double func_1(double x);
double func_1_(double x);
double func_2(double x);
double func_2_(double x);
double func_3(double x);
double func_3_(double x);
double func_4(double x);
double func_4_(double x);

int main(){
	Secante obj;
	double x0;
	int err;
	char op;
	
	printf("1-Secante\n");
	printf("2-Newton\n");
	cin >> op;
	
	/////////
	char caso;
	printf("Problema 1. Digite a letra da funcao ::\n");
	printf("a\nb\nc\nd\n");
	printf("Aqui :: ");
	cin >> caso;
	////////

	printf("Digite a precisao (modulo do expoente do 10).\n");
	cin >> err;
	obj.set_err(err);

	printf("Digite x0 : \n");
	cin >> x0;
	obj.set_x1(x0);
	
	if(op == '1'){
		printf("Digite x1\n");
		cin >> x0;
		obj.set_x2(x0);
	}

	printf("Digite o limite de iteracoes:\n");
	cin >> err;
	obj.set_precision();

	if(caso == 'a'){
		if(op == '1')		printf("%lf\n", obj.secante(func_1, err));
		else				printf("%lf\n", obj.newton(func_1, func_1_, err));
	}
	else if(caso == 'b'){
		if(op == '1')		printf("%lf\n", obj.secante(func_2, err));
		else				printf("%lf\n", obj.newton(func_2, func_2_, err));
	}
	else if(caso == 'c'){
		if(op == '1')		printf("%lf\n", obj.secante(func_3, err));
		else				printf("%lf\n", obj.newton(func_3, func_3_, err));
	}
	else if(caso == 'd'){
		if(op == '1')		printf("%lf\n", obj.secante(func_4, err));
		else				printf("%lf\n", obj.newton(func_4, func_4_, err));
	}
	return 0;
}
inline double func_1(double x){return (pow(x,3) - 2*x - 2);}
inline double func_1_(double x){return (3*pow(x,2) - 2);}

inline double func_2(double x){return (exp(x) + x - 7);}
inline double func_2_(double x){return (x*exp(x) + 1);}

inline double func_3(double x){return (exp(x) + sin(x) - 4);}
inline double func_3_(double x){return (x*exp(x) + cos(x));}

inline double func_4(double x){return pow(exp(1.0), -x) - log10(x);}
inline double func_4_(double x){return (-exp(-x) -(1/(x*log10(exp(1.0) ) ) ) );}
