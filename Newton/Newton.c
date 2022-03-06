#include <math.h>
#include <stdio.h>
#define e 0.00001
#define deltaX 0.00000001

double getF(double x)
{
    return pow(x, 2) - 3; // change function here
}

double firstDerivative(double x)
{
    return (getF(x + deltaX) - getF(x)) / deltaX;
}

double secondDerivative(double x)
{
    double x1 = firstDerivative(x);
    double x2 = firstDerivative(x + deltaX);
    return (x2 - x1) / deltaX;
}

int usabilityCheck(double left, double right)
{
    if ((getF(left) < 0) && (getF(right) < 0))
    {
        return -1;
    }
    if ((getF(left) > 0) && (getF(right) > 0))
    {
        return -1;
    }
    if ((firstDerivative(left) < 0) && (firstDerivative(right) > 0))
    {
        return -1;
    }
    if ((firstDerivative(left) > 0) && (firstDerivative(right) < 0))
    {
        return -1;
    }
    if ((secondDerivative(left) < 0) && (secondDerivative(right) > 0))
    {
        return -1;
    }
    if ((secondDerivative(left) > 0) && (secondDerivative(right) < 0))
    {
        return -1;
    }
    return 0;
}

double initApproximation(double left, double right)
{
    if ((getF(left) < 0) && (secondDerivative(left) < 0))
    {
        return left;
    }
    if ((getF(left) > 0) && (secondDerivative(left) > 0))
    {
        return left;
    }
    return right;
}

int main()
{
    double left, right, x0, x1;
    FILE* in;
    FILE* out;
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    if (in == NULL || out == NULL)
    {
        fprintf(out, "ошибка открытия файла\n");
        return -1;
    }

    fscanf(in, "%lf", &left);
    fscanf(in, "%lf", &right);

    if (usabilityCheck(left, right) == -1)
    {
        fprintf(out, "Нарушены условия применимости");
        return -1;
    }

    x1 = initApproximation(left, right);

    do
    {
        x0 = x1;
        x1 = x0 - getF(x0) / firstDerivative(x0);
    } while (fabs(x1 - x0) > e);

    fprintf(out, "x = %.8lf", x1);
    return x1;
}