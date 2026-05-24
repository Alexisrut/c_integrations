#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "integration.h"


#define EPS 0.0001
#define RANDOM_TESTS 10000


/*
    Сравнение чисел с плавающей точкой
*/
int almost_equal(double a, double b, double eps)
{
    return fabs(a - b) < eps;
}


/*
    Случайное число на промежутке
*/
double random_double(double min, double max)
{
    return min +
        ((double)rand() / RAND_MAX) * (max - min);
}


/*
    Аналитические функции
*/

double analytical_f1(double x)
{
    return 0.35 * x * x - 0.95 * x + 2.7;
}

double analytical_f2(double x)
{
    return 3.0 * x + 1.0;
}

double analytical_f3(double x)
{
    return 1.0 / (x + 2.0);
}

double analytical_df1(double x)
{
    return 0.7 * x - 0.95;
}

double analytical_df2(double x)
{
    return 3.0;
}

double analytical_df3(double x)
{
    return -1.0 / ((x + 2.0) * (x + 2.0));
}


int main()
{
    srand(time(NULL));

    printf("\n========== ASM FUNCTION TESTS ==========\n\n");


    /*
        Массовое тестирование f1
    */
    for (int i = 0; i < RANDOM_TESTS; i++)
    {
        double x = random_double(-1000.0, 1000.0);

        double expected = analytical_f1(x);
        double actual = f1(x);

        assert(almost_equal(actual, expected, EPS));
    }

    printf("f1 random stress tests passed\n");


    /*
        Массовое тестирование f2
    */
    for (int i = 0; i < RANDOM_TESTS; i++)
    {
        double x = random_double(-1000.0, 1000.0);

        double expected = analytical_f2(x);
        double actual = f2(x);

        assert(almost_equal(actual, expected, EPS));
    }

    printf("f2 random stress tests passed\n");


    /*
        Массовое тестирование f3
    */
    for (int i = 0; i < RANDOM_TESTS; i++)
    {
        double x = random_double(-1.9, 1000.0);

        double expected = analytical_f3(x);
        double actual = f3(x);

        assert(almost_equal(actual, expected, EPS));
    }

    printf("f3 random stress tests passed\n");


    printf("\n========== DERIVATIVE TESTS ==========\n\n");


    /*
        df1
    */
    for (int i = 0; i < RANDOM_TESTS; i++)
    {
        double x = random_double(-1000.0, 1000.0);

        double expected = analytical_df1(x);
        double actual = df1(x);

        assert(almost_equal(actual, expected, EPS));
    }

    printf("df1 stress tests passed\n");


    /*
        df2
    */
    for (int i = 0; i < RANDOM_TESTS; i++)
    {
        double x = random_double(-1000.0, 1000.0);

        double expected = analytical_df2(x);
        double actual = df2(x);

        assert(almost_equal(actual, expected, EPS));
    }

    printf("df2 stress tests passed\n");


    /*
        df3
    */
    for (int i = 0; i < RANDOM_TESTS; i++)
    {
        double x = random_double(-1.9, 1000.0);

        double expected = analytical_df3(x);
        double actual = df3(x);

        assert(almost_equal(actual, expected, EPS));
    }

    printf("df3 stress tests passed\n");


    printf("\n========== EDGE CASE TESTS ==========\n\n");


    /*
        Граничные случаи
    */

    assert(almost_equal(f1(0.0), 2.7, EPS));
    assert(almost_equal(f2(0.0), 1.0, EPS));
    assert(almost_equal(f3(0.0), 0.5, EPS));

    assert(almost_equal(df1(0.0), -0.95, EPS));
    assert(almost_equal(df2(0.0), 3.0, EPS));
    assert(almost_equal(df3(0.0), -0.25, EPS));

    printf("Edge case tests passed\n");


    printf("\n========== LARGE NUMBER TESTS ==========\n\n");


    /*
        Очень большие значения
    */

    double big = 1000000.0;

    assert(isfinite(f1(big)));
    assert(isfinite(f2(big)));
    assert(isfinite(f3(big)));

    assert(isfinite(df1(big)));
    assert(isfinite(df2(big)));
    assert(isfinite(df3(big)));

    printf("Large number tests passed\n");


    /*
====================================================
                INTEGRAL TESTS
====================================================
*/

printf("\n========== EXTENDED INTEGRAL TESTS ==========\n\n");


/*
    f1(x) = 0.35x² - 0.95x + 2.7

    Первообразная:
    F(x) =
    (0.35/3)x³ - (0.95/2)x² + 2.7x
*/
for (int i = 0; i < 100; i++)
{
    double a = random_double(-10.0, 10.0);
    double b = random_double(a, a + 10.0);

    long double numeric =
        integral(
            "f1",
            a,
            b,
            0.0001
        );

    long double analytic =
        (0.35 / 3.0) * (b*b*b - a*a*a)
        - (0.95 / 2.0) * (b*b - a*a)
        + 2.7 * (b - a);

    assert(
        fabsl(numeric - analytic) < 0.05
    );
}

printf("Random integral tests for f1 passed\n");


/*
    f2(x) = 3x + 1

    F(x) = 1.5x² + x
*/
for (int i = 0; i < 100; i++)
{
    double a = random_double(-100.0, 100.0);
    double b = random_double(a, a + 50.0);

    long double numeric =
        integral(
            "f2",
            a,
            b,
            0.0001
        );

    long double analytic =
        1.5 * (b*b - a*a)
        + (b - a);

    assert(
        fabsl(numeric - analytic) < 0.05
    );
}

printf("Random integral tests for f2 passed\n");


/*
    f3(x) = 1/(x+2)

    F(x) = ln|x+2|
*/

/*
    Очень маленькие интервалы
*/
for (int i = 0; i < 1000; i++)
{
    double a = random_double(-10.0, 10.0);
    double b = a + 0.0001;

    long double result =
        integral(
            "f1",
            a,
            b,
            0.000001
        );

    assert(isfinite(result));
}

printf("Small interval tests passed\n");


/*
    Большие интервалы
*/
for (int i = 0; i < 100; i++)
{
    double a = random_double(-1000.0, 0.0);
    double b = random_double(0.0, 1000.0);

    long double result =
        integral(
            "f2",
            a,
            b,
            0.01
        );

    assert(isfinite(result));
}

printf("Large interval tests passed\n");


/*
====================================================
                    ROOT TESTS
====================================================
*/

printf("\n========== EXTENDED ROOT TESTS ==========\n\n");


/*
    Проверка:
    f1(x) = f2(x)
*/
for (int i = 0; i < 100; i++)
{
    long double r =
        root(
            "f1",
            "f2",
            -5.0,
            5.0,
            0.0001,
            derivative_f,
            derivative_g
        );

    assert(
        fabsl(f1(r) - f2(r)) < 0.01
    );
}

printf("Repeated root tests f1=f2 passed\n");


/*
    Проверка:
    f2(x) = f3(x)
*/
for (int i = 0; i < 100; i++)
{
    long double r =
        root(
            "f2",
            "f3",
            -1.0,
            1.0,
            0.0001,
            derivative_f,
            derivative_g
        );

    assert(
        fabsl(f2(r) - f3(r)) < 0.01
    );
}

printf("Repeated root tests f2=f3 passed\n");


/*
    Проверка:
    f1(x) = f3(x)
*/
for (int i = 0; i < 100; i++)
{
    long double r =
        root(
            "f1",
            "f3",
            -2.0,
            5.0,
            0.0001,
            derivative_f,
            derivative_g
        );
    printf("%lf %lf %lf\n", f1(r), f3(r), r);
    assert(
        fabsl(f1(r) - f3(r)) < 0.0001
    );
}

printf("Repeated root tests f1=f3 passed\n");


/*
    Случайные eps
*/
for (int i = 0; i < 100; i++)
{
    double eps =
        random_double(
            0.000001,
            0.001
        );

    long double r =
        root(
            "f1",
            "f2",
            -5.0,
            5.0,
            eps,
            derivative_f,
            derivative_g
        );

    assert(
        fabsl(f1(r) - f2(r)) < 0.1
    );
}

printf("Random epsilon root tests passed\n");


/*
    Стресс-тест root
*/
for (int i = 0; i < 10000; i++)
{
    long double r =
        root(
            "f1",
            "f2",
            -5.0,
            5.0,
            0.0001,
            derivative_f,
            derivative_g
        );

    assert(isfinite(r));
}

printf("Root stress tests passed\n");


/*
    Стресс-тест integral
*/
for (int i = 0; i < 10000; i++)
{
    long double r =
        integral(
            "f1",
            -10.0,
            10.0,
            0.001
        );

    assert(isfinite(r));
}

printf("Integral stress tests passed\n");


    printf("\n========== INTEGRAL TESTS ==========\n\n");


    /*
        Интеграл f1
        Аналитическое значение:

        integral(0.35x² - 0.95x + 2.7)
        от 0 до 2

        ≈ 4.333333
    */

    long double integral_f1 =
        integral(
            "f1",
            0.0,
            2.0,
            0.0001
        );

    printf(
        "Integral f1 [0,2] = %Lf\n",
        integral_f1
    );

    assert(fabsl(integral_f1 - 4.433333) < 0.01);


    /*
        Интеграл f2
        ∫(3x+1)dx от 0 до 1 = 2.5
    */

    long double integral_f2 =
        integral(
            "f2",
            0.0,
            1.0,
            0.0001
        );

    printf(
        "Integral f2 [0,1] = %Lf\n",
        integral_f2
    );

    assert(fabsl(integral_f2 - 2.5) < 0.01);

    printf("Integral tests passed\n");


    printf("\n========== ROOT TESTS ==========\n\n");


    /*
        Корень:
        f1(x) = f2(x)
    */

    long double r1 =
        root(
            "f1",
            "f2",
            0.0,
            1.0,
            0.0001,
            derivative_f,
            derivative_g
        );

    printf("Root f1=f2 : %Lf\n", r1);

    assert(fabsl(f1(r1) - f2(r1)) < 0.01);


    /*
        Корень:
        f2(x) = f3(x)
    */

    long double r2 =
        root(
            "f2",
            "f3",
            -1.0,
            1.0,
            0.0001,
            derivative_f,
            derivative_g
        );

    printf("Root f2=f3 : %Lf\n", r2);

    assert(fabsl(f2(r2) - f3(r2)) < 0.01);

    printf("Root tests passed\n");


    printf("\n========== PERFORMANCE STRESS TEST ==========\n\n");


    /*
        Нагрузочный тест
    */

    for (int i = 0; i < 100000; i++)
    {
        double x = random_double(-100.0, 100.0);

        f1(x);
        f2(x);
        f3(x);

        df1(x);
        df2(x);
        df3(x);
    }

    printf("Performance stress tests passed\n");


    printf("\n========== ALL TESTS PASSED ==========\n\n");

    return 0;
}