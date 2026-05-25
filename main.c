#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "integration.h"

void help(void) {
    printf("Usage: [-test] [-iter] [-root] [-help]\n");
    printf("-help = show this\n");
    printf("-test = run tests. 1 Input example: root f1 f3 -1.9 -1.5 0.0001\n");
    printf("2 Input example: iter f1 -1.9 -1.5 0.0001\n");
}


void tests(int argc, char* argv[]) {
    if (argc <= 4) {
        printf("Not enough arguments\n");
        return;
    }
    if (strcmp(argv[2], "root") == 0) {
        printf("Root test\n");
        if (argc < 8) {
            printf("Not enough arguments\n");
            return;
        }
        printf("Test: %f\n", root(argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]), derivative_f, derivative_g));
    }
    if (strcmp(argv[2], "iter") == 0) {
        if (argc < 7) {
            printf("Not enough arguments\n");
            return;
        }
        printf("Test: %f\n", integral(argv[3], atof(argv[4]), atof(argv[5]), atof(argv[6])));
    }
    return;
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-test") == 0) {
            tests(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "-help") == 0) {
            help();
            return 0;
        } else {
            printf("Unknown argument: %s\n", argv[i]);
            return 0;
        }
    }
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