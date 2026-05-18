#include "integration.h"

char* derivative_f(char f[], long double eps1) {
    
}

char* derivative_g(char g[], long double eps1) {
    
}

long double root(char f[], char g[], long double a, long double b, long double eps1, 
                    char* (*derivative_f)(char[], long double), char* (*derivative_g)(char[], long double)) {
    char* df = derivative_f(f, eps1); //Пример вызова функции вычисления производной
    char* dg = derivative_g(g, eps1);
}

long double integral(char f[], long double a, long double b, long double eps2) {

}