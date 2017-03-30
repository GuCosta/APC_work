#include <cstdio>
#include <cmath>
#include <iostream>
#ifndef _SECANTE_H_
#define _SECANTE_H_
inline double rel_error(double xa, double xb);


class Secante{
	double x1,x2;
	int err;
	double precision;
public:
	inline void set_x1(double x){x1=x;}
	inline void set_x2(double x){x2=x;}
	inline void set_err(int x){err = x;}
	inline void set_precision(){precision = pow(10, -err)/2;}

	inline double get_root(){return x1;}
	inline double get_err(){return err;}
	inline double get_precision(){return precision;}
	inline double rel_error(double a, double b){return fabs(a - b)/std :: max(fabs(a), 1.0);}

	double secante(double(&f)(double  x), int i){
		int k=0;
		double x3 = x2 - (x2-x1)*f(x2)/(f(x2) - f(x1));
		while(rel_error(x1, x2) > precision){
			printf("f(x1) == %lf\n", f(x1));
			printf("f(x2) == %lf\n", f(x2));
	        printf("x1 == %lf    x2 == %lf\n", x1,x2);
			x3 = x2 - (((x2-x1)/(f(x2)-f(x1))) * f(x2));
			//x3 = x2 - (x2-x1)*f(x2)/(f(x2) - f(x1));
			x1 = x2;
			x2 = x3;
			printf("%lf\n", x3);
		}
		
		if(k==i)	printf("Erro.\n");
		return x1;
	}
	double newton(double(&f)(double  x), double(&f_)(double  x), int i){
		x2=x1;	//preprocessamento
		int k=0;
		do{
			x1 = x2;
			x2= x1 - f(x1)/f_(x1);		

		}
		while(rel_error(x2,x1) > precision && k < i);

		if(k==i)	printf("Erro.\n");
		return x1;
	}
};
#endif