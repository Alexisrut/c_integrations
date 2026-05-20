#ifndef INTEGRATION_H
#define INTEGRATION_H

extern double f1 (double x);
extern double f2 (double x);
extern double f3 (double x);
extern double df1 (double x);
extern double df2 (double x);
extern double df3 (double x);


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