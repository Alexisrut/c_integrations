#include <math.h>
#include <stdio.h>
#include <string.h>
#include "integration.h"


//Число итераций последнего вызова root.
int root_iterations = 0;

//Возвращает имя производной для функции f.
/**/
char* derivative_f(char f[]) {
    if (strcmp(f, "f1") == 0) {
        return "df1";
    }
    if (strcmp(f, "f2") == 0) {
        return "df2";
    }

    return "df3";
}

//аналогично
char* derivative_g(char g[]) {
    if (strcmp(g, "f1") == 0) {
        return "df1";
    }
    if (strcmp(g, "f2") == 0) {
        return "df2";
    }

    return "df3";
}


//Вычисляет значение функции.
double y(char f[], double x) {
    if (strcmp(f, "f1") == 0) {
        return f1(x);
    }
    if (strcmp(f, "f2") == 0) {
        return f2(x);
    }

    return f3(x);
}


//Вычисляет значение производной.
double dy(char df[], double x) {
    if (strcmp(df, "df1") == 0) {
        return df1(x);
    }
    if (strcmp(df, "df2") == 0) {
        return df2(x);
    }

    return df3(x);
}

/*
 * F(x) = f(x) - g(x).
 * Точка пересечения f и g находится как корень F(x) = 0.
*/
double F(char f[], char g[], double x) {
    return y(f, x) - y(g, x);
}

//F'(x) = f'(x) - g'(x).
double dF(char df[], char dg[], double x) {
    return dy(df, x) - dy(dg, x);
}


//Поиск корня уравнения f(x) = g(x) на отрезке [a, b].
double root(char f[], char g[], double a, double b, double eps1, char* (*derivative_f_ptr)(char[]), char* (*derivative_g_ptr)(char[])) {
    double left = a;
    double right = b;
    double f_left;
    double f_right;
    double new_left;
    double new_right;
    double der;
    int tangent_left = 0;

    char* df = derivative_f_ptr(f);
    char* dg = derivative_g_ptr(g);

    root_iterations = 0;

    f_left = F(f, g, left);
    f_right = F(f, g, right);

    if (f_left == 0.0L) {
        return left;
    }
    if (f_right == 0.0L) {
        return right;
    }

    if (f_left * f_right > 0.0L) {
        printf("Bad segment [%lf; %lf] for %s and %s\n", a, b, f, g);
        return 0.0L;
    }

    /*
     * Сначала пробуем понять, можно ли делать касательную из левого конца.
     * Если шаг Ньютона из left попадает внутрь отрезка, используем его.
     * Иначе касательную будем делать из правого конца.
     */
    der = dF(df, dg, left);
    if (der != 0.0L) {
        double test = left - F(f, g, left) / der;
        if (test > left && test < right) {
            tangent_left = 1;
        }
    }

    while (fabsl(right - left) > eps1) {
        f_left = F(f, g, left);
        f_right = F(f, g, right);

        if (tangent_left) {
             //Левый конец двигаем методом касательных.
            der = dF(df, dg, left);
            if (der == 0.0L) {
                new_left = (left + right) / 2.0L;
            } else {
                new_left = left - f_left / der;
            }

            //Правый конец двигаем методом хорд.
            new_right = right - f_right * (new_left - right) / (F(f, g, new_left) - f_right);

        } else {
            //Левый конец двигаем методом хорд.
            new_left = left - f_left * (right - left) / (f_right - f_left);

            // Правый конец двигаем методом касательных.
            der = dF(df, dg, right);
            if (der == 0.0L) {
                new_right = (left + right) / 2.0L;
            } else {
                new_right = right - f_right / der;
            }
        }

        if (new_left < new_right) {
            left = new_left;
            right = new_right;
        } else {
            left = new_right;
            right = new_left;
        }

        root_iterations++;
    }

    return (left + right) / 2.0L;
}


//Вычисление интеграла от f на [a, b] формулой средних прямоугольников.
double integral(char f[], double a, double b, double eps2) {
    int n = 1;
    int i;
    double h;
    double x;
    double sum;
    double previous = 0.0L;
    double current;

    h = b - a;
    x = a + h / 2.0L;
    current = h * y(f, x);

    while (fabsl(current - previous) > eps2 && n <= 1048576) {
        previous = current;
        n *= 2;
        h = (b - a) / n;
        sum = 0.0L;

        for (i = 0; i < n; i++) {
            x = a + h * (i + 0.5L);
            sum += y(f, x);
        }

        current = sum * h;
    }

    return current;
}
