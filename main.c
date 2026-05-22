#include <stdio.h>

#include "integration.h"

int main()
{
    /*
        Проверка ASM-функций
    */

    double x = 2.0;

    printf("f1(%lf) = %lf\n", x, f1(x));
    printf("f2(%lf) = %lf\n", x, f2(x));
    printf("f3(%lf) = %lf\n", x, f3(x));

    printf("\n");

    printf("df1(%lf) = %lf\n", x, df1(x));
    printf("df2(%lf) = %lf\n", x, df2(x));
    printf("df3(%lf) = %lf\n", x, df3(x));

    printf("\n");


    /*
        Интеграл
    */

    long double integral_result =
        integral(
            "f1",
            0.0,
            2.0,
            0.0001
        );

    printf(
        "Integral of f1 on [0,2] = %Lf\n",
        integral_result
    );

    printf("\n");


    /*
        Корень уравнения:
        f1(x) = f2(x)
    */

    long double root_result =
        root(
            "f1",
            "f2",
            0.0,
            1.0,
            0.0001,
            derivative_f,
            derivative_g
        );

    printf(
        "Root of f1(x) = f2(x): %Lf\n",
        root_result
    );

    return 0;
}