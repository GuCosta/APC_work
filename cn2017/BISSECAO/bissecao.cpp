#include <cstdio>
#include <cmath>
#include <iostream>
#include "bissecao.h"

void Bissecao :: set_a(double x){a=x;}
void Bissecao :: set_b(double x){b=x;}
void Bissecao :: set_root(double x){root=(a+b)/2;}	//motivo : padronizacao de interface
void Bissecao :: set_err(int x){err=x;}
void Bissecao :: set_precision(){precision = pow(10, -err)/2;}
double Bissecao :: func_a(double(&f)(double)){return f(a);}
double Bissecao :: func_b(double(&f)(double)){return f(b);}
double Bissecao :: func_root(double(&f)(double)){return f(root);}
double Bissecao :: get_a(){return a;}
double Bissecao :: get_b(){return b;}
double Bissecao :: get_root(){return root;}
double Bissecao :: rel_error(double a, double b){return fabs(a - b)/std :: max(fabs(a), 1.0);}
void Bissecao :: bissecao(double(&f)(double)){
	double arg1, arg2, tmp;
	int i=0;
	do{
		i++;
		set_root(0);
		arg1 = get_root();
		printf("r == %.15lf\n", get_root());
		if(func_root(f)*func_a(f) > 0.0000001){
			set_a(arg1);	arg2 = get_b();
		}
		else if(func_root(f)*func_b(f) > 0.0000001){
			set_b(arg1);	arg2 = get_a();			
		}
		else{	tmp = precision;
				precision = 99999999999;	//apenasparasair do loop
			}
		
		printf("%.15lf > %.15lf \? \n", rel_error(arg1, arg2), precision );
	}while(rel_error(arg1, arg2) > precision);
	precision = tmp;
	printf("%.15lf > %.15lf \? \n", rel_error(arg1, arg2), precision );
	printf("Precision :: %20lf\n", precision);
	printf("i == %d <-----> root == %lf\n", 200 - i, get_root());
	}
void Bissecao :: intervalos(double(&f)(double)){
	double tmp;
	do{
	printf("Digite um extremo do intervalo. Teste.\n");
	scanf("%lf", &tmp);	set_a(tmp);
	printf("Digite um extremo do intervalo.\n");
	scanf("%lf", &tmp);	set_b(tmp);
	printf("%lf ------ %lf\n",func_a(f), func_b(f));
	}while( f(get_a())*f(get_b()) >0);
	printf("a == %.15lf , b == %.15lf\n", get_a(),get_b());
	}


