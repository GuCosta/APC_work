#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
//#define fabs(a)	(a) >= 0 ? (a) : (-a)
#define PI 3.14159265
#define erro 0.000000001
using namespace std;
double fa(double x);
double fb(double x);
double fc(double x);

int main(void){
	char op;
	double a, b;
	cout << "Item 1. Selecione a letra : 'a', 'b' ou 'c'." << endl;
	cin >> op;
	switch(op){
		case 'a' : 
			#define func fa
			break;
		case 'b':
			#define func fb
			break;
		case 'c':
			#define func fc
			break;
		default:
			#define	func fa
			break;
	}
	
	do{
	cout << "Digite um extremo do intervalo" << endl;
	cin >> a;
	cout << "Digite outro extremo do intervalo" << endl;
	cin >> b;
	printf("%lf\n", func(a) * func(b));
	}while(func(a) * func(b) > 0.0000001);
	int stp=0;
	printf("stp == 0\n");
//	cout << fabs(func(a)) << "  vs  " << fabs(func(b)) << endl;
	if(fabs(func(b)) <= erro){
		cout << "Raiz : " << b << endl;
		return 0;
	}
	if(fabs(func(a)) == erro){
		cout << "Raiz : " << a << endl;
		return 0;
	}
	double c;
	while(fabs(func(a) - func(b)) >= 0.0000001){
		stp++;
		c = (a+b)/2;
		printf("%.10lf\n",c );
		if(func(a)*func(c) < 0)	b=c;
		else if(func(b)*func(c) < 0)	a=c;
		else if (fabs(func(c)) < erro){
			cout << "[Aquiii] Raiz : " << c << endl;
			break;
		}
	}
	printf("%.10lf --- %.10lf \n", func(a), func(b));
	c = (a+b)/2;
	cout << "Raiz : aquiii " << c << endl;
	cout << "steps :: " << stp << endl;
	return 0;
}

double fa(double x){
	return (pow(x, 3) - 2);
}
double fb(double x){
	return (pow(x, 3) - 3);
}
double fc(double x){
	return (pow(x, 3) - 5);
}