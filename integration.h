#ifndef INTEGRATION_H
#define INTEGRATION_H

extern char* derivative_f(char f[], long double eps1);

extern char* derivative_g(char g[], long double eps1);

extern long double root(
    char f[],
    char g[],
    long double a,
    long double b,
    long double eps1,
    char* (*derivative_f)(char[], long double),
    char* (*derivative_g)(char[], long double)
);

extern long double integral(
    char f[],
    long double a,
    long double b,
    long double eps2
);

#endif