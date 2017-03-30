#include <cstdio>
#include <cmath>
#include <iostream>
#ifndef _PONTOFIXO_H_
#define _PONTOFIXO_H_

inline double rel_error(double xa, double xb);
class PontoFixo{
	double x0;
	int err;
	double root;
	double precision;
public:
	inline void set_x0(double x){x0=x;}
	inline void set_err(int x){err = x;}
	inline void set_precision(){precision = pow(10, -err)/2;}

	inline double get_root(){return root;}
	inline double get_err(){return err;}
	inline double get_precision(){return precision;}

	inline double rel_error(double a, double b){return fabs(a - b)/std :: max(fabs(a), 1.0);}

	double pontofixo(double x, double(&f)(double), int stop){	//caso de merda, stop
		int i=1;
		double min=1000000007, a;
		root = f(x0);
		printf("debug :: rel_error incial == %.10lf\n", rel_error(root, x0));
		while(rel_error(root, x0)  > get_precision() && (a =fabs(root - x0)) <= min && i < 100){
		min = a;
		x0=root;
		root = f(x0);
		printf("Iteracao %d , erro %.10lf\n",i++, rel_error(root, x0) );
		printf("x0 == %lf,  root == %lf\n", x0,root);
		}
		if(a>min)	printf("ERRO\n");
		else
			printf("Raiz :: %.15lf\n", root);

		return root;
	}

};
#endif