#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "integration.h"

int main()
{
    long double eps = 0.0001;

    long double x13 = root("f1", "f3", -1.9, -1.5, eps, derivative_f, derivative_g);
    long double x23 = root("f2", "f3", -0.5, 0.0, eps, derivative_f, derivative_g);
    long double x12 = root("f1", "f2", 0.0, 1.0, eps, derivative_f, derivative_g);

    long double area =
        integral("f1", x13, x23, eps) - integral("f3", x13, x23, eps)
        +
        integral("f1", x23, x12, eps) - integral("f2", x23, x12, eps);

    printf("x13 = %Lf\n", x13);
    printf("x23 = %Lf\n", x23);
    printf("x12 = %Lf\n", x12);

    printf("Area = %Lf\n", area);

    assert(fabsl(area - 5.12019L) < 0.01L);

    return 0;
}