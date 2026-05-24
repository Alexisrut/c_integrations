#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "integration.h"

#define EPS 0.0001
#define RANDOM_TESTS 10000

int check(double a, double b, double eps) {
    return fabs(a - b) < eps;
}

double random_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}
double c_f1(double x) {
    return 0.35 * x * x - 0.95 * x + 2.7;
}

double c_f2(double x) {
    return 3.0 * x + 1.0;
}

double c_f3(double x) {
    return 1.0 / (x + 2.0);
}

double c_df1(double x) {
    return 0.7 * x - 0.95;
}

double c_df2(double x) {
    return 3.0;
}

double c_df3(double x) {
    return -1.0 / ((x + 2.0) * (x + 2.0));
}

int main(void) {
    srand(time(NULL));

    for (int i = 0; i < RANDOM_TESTS; i++) {
        double x = random_double(-1000.0, 1000.0);

        double c_value = c_f1(x);
        double for_check = f1(x);

        assert(check(for_check, c_value, EPS));
    }

    for (int i = 0; i < RANDOM_TESTS; i++) {
        double x = random_double(-1000.0, 1000.0);

        double c_value = c_f2(x);
        double for_check = f2(x);

        assert(check(for_check, c_value, EPS));
    }

    for (int i = 0; i < RANDOM_TESTS; i++) {
        double x = random_double(-1.9, 1000.0);

        double c_value = c_f3(x);
        double for_check = f3(x);

        assert(check(for_check, c_value, EPS));
    }

    for (int i = 0; i < RANDOM_TESTS; i++) {
        double x = random_double(-1000.0, 1000.0);

        double c_value = c_df1(x);
        double for_check = df1(x);

        assert(check(for_check, c_value, EPS));
    }

    for (int i = 0; i < RANDOM_TESTS; i++) {
        double x = random_double(-1000.0, 1000.0);

        double c_value = c_df2(x);
        double for_check = df2(x);

        assert(check(for_check, c_value, EPS));
    }

    for (int i = 0; i < RANDOM_TESTS; i++) {
        double x = random_double(-1.9, 1000.0);

        double c_value = c_df3(x);
        double for_check = df3(x);

        assert(check(for_check, c_value, EPS));
    }

    assert(check(f1(0.0), 2.7, EPS));
    assert(check(f2(0.0), 1.0, EPS));
    assert(check(f3(0.0), 0.5, EPS));

    assert(check(df1(0.0), -0.95, EPS));
    assert(check(df2(0.0), 3.0, EPS));
    assert(check(df3(0.0), -0.25, EPS));

    for (int i = 0; i < 100; i++) {
        double a = random_double(-10.0, 10.0);
        double b = random_double(a, a + 10.0);

        long double numeric = integral("f1", a, b, EPS);

        long double analytic = (0.35 / 3.0) * (b * b * b - a * a * a) - (0.95 / 2.0) * (b * b - a * a) + 2.7 * (b - a);

        assert(
            fabsl(numeric - analytic) < 0.05
        );
    }

    for (int i = 0; i < 100; i++) {
        double a = random_double(-100.0, 100.0);
        double b = random_double(a, a + 50.0);

        long double numeric = integral("f2", a, b, EPS);

        long double analytic = 1.5 * (b * b - a * a) + (b - a);

        assert(fabsl(numeric - analytic) < 0.05);
    }

    for (int i = 0; i < 1000; i++){
        double a = random_double(-10.0, 10.0);
        double b = a + 0.0001;

        long double result = integral("f1", a, b, EPS);

        assert(isfinite(result));
    }

    for (int i = 0; i < 100; i++) {
        double a = random_double(-1000.0, 0.0);
        double b = random_double(0.0, 1000.0);

        long double result =
            integral("f2", a, b, EPS);

        assert(isfinite(result));
    }

    for (int i = 0; i < 100; i++) {
        long double r =
            root("f1", "f2", -5.0, 5.0, EPS, derivative_f, derivative_g);

        assert(
            fabsl(f1(r) - f2(r)) < EPS
        );
    }

    for (int i = 0; i < 100; i++) {
        long double r =
            root("f2", "f3", -1.0, 1.0, EPS, derivative_f, derivative_g);

        assert(
            fabsl(f2(r) - f3(r)) < EPS
        );
    }

    for (int i = 0; i < 100; i++){
        long double r =
            root("f1", "f3", -1.9, 5.0, EPS, derivative_f, derivative_g);
        assert(
            fabsl(f1(r) - f3(r)) < EPS
        );
    }
        long double integral_f1 = integral("f1", 0.0, 2.0, EPS);
        assert(fabsl(integral_f1 - 4.433333) < 0.01);

        long double integral_f2 = integral("f2", 0.0, 1.0, EPS);
        assert(fabsl(integral_f2 - 2.5) < 0.01);

        long double integral_f3 = integral("f3", -1.0, 1.0, EPS);
        assert(fabsl(integral_f3 - 1.098) < 0.01);

        long double r1 = root("f1", "f2", 0.0, 1.0, EPS, derivative_f, derivative_g);
        assert(fabsl(f1(r1) - f2(r1)) < 0.01);


        long double r2 = root("f2", "f3", -1.0, 1.0, EPS, derivative_f, derivative_g);
        assert(fabsl(f2(r2) - f3(r2)) < 0.01);
        
        printf("All tests passed\n");
        return 0;
}