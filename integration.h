#ifndef INTEGRATION_H
#define INTEGRATION_H

char* derivative_f(char f[], long double eps1);

char* derivative_g(char g[], long double eps1);

long double root(
    char f[],
    char g[],
    long double a,
    long double b,
    long double eps1,
    char* (*derivative_f)(char[], long double),
    char* (*derivative_g)(char[], long double)
);

long double integral(
    char f[],
    long double a,
    long double b,
    long double eps2
);

#endif