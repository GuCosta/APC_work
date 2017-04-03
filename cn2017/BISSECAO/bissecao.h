#ifndef _BISSECAO_H_
#define _BISSECAO_H_
class Bissecao{
	double a, b;	//extremos do intervalo inicial
	double x0;
	double root;
	int err;		//natural cujo oposto eleva 10 e resulta na precisao desejada
	double precision;
public:

void set_a(double x);
void set_b(double x);
void set_root(double x);	//motivo : padronizacao de interface
void set_err(int x);
void set_precision(void);
double func_a(double(&f)(double));
double func_b(double(&f)(double));
double func_root(double(&f)(double));
double get_a(void);
double get_b(void);
double get_root(void);
double rel_error(double a, double b);
void bissecao(double(&f)(double));
void intervalos(double(&f)(double));
};
#endif
