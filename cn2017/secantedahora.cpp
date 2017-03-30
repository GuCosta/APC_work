#include<bits/stdc++.h>

using namespace std;

double e = 2.718281828;

double f(double x){
    double p =  pow(exp(1.0), -x) - log10(x);
    printf("Funcao :: %lf\n", p);
    return
}

int main(){
    double x1,x2,x3,erro = 99999999;
    scanf("%lf %lf",&x1,&x2);
    while(erro > 1e-12){
        printf("x1 == %lf    x2 == %lf\n", x1,x2);
        x3 = x2 - (((x2-x1)/(f(x2)-f(x1))) * f(x2));
        printf("%lf\n",x3);
        x1 = x2;
        x2 = x3;
        erro = fabs((x2 - x1)/x2);
    }
return 0;
}
