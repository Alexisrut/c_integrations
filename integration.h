#ifndef INTEGRATION_H
#define INTEGRATION_H

extern double f1 (double x);
extern double f2 (double x);
extern double f3 (double x);
extern double df1 (double x);
extern double df2 (double x);
extern double df3 (double x);

extern char* derivative_f(char f[]);
extern char* derivative_g(char g[]);


extern double root(
    char f[], 
    char g[], 
    double a, 
    double b, 
    double eps1, 
    char* (*derivative_f_ptr)(char[]), 
    char* (*derivative_g_ptr)(char[])
);

extern double integral(
    char f[], 
    double a, 
    double b, 
    double eps2
);

#endif