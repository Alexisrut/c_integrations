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
}