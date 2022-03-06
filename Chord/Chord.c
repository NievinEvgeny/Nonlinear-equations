#include <math.h>
#include <stdio.h>
#define e 0.00001

double getF(double x)
{
    return pow(x, 2) - 3; // change function here
}

int checkForRoots(double left, double right)
{
    //-2 = no roots, -1 = left is root, 1 = right is root, 0 = have roots
    if (getF(left) == 0)
    {
        return -1;
    }
    if (getF(right) == 0)
    {
        return 1;
    }
    if ((getF(left) < 0) && (getF(right) < 0))
    {
        return -2;
    }
    if ((getF(left) > 0) && (getF(right) > 0))
    {
        return -2;
    }
    return 0;
}

double findNextX(double left, double right)
{
    return ((left * getF(right) - right * getF(left)) / (getF(right) - getF(left)));
}

int main()
{
    double left, right, x;
    int check;

    FILE* in;
    FILE* out;
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    if (in == NULL || out == NULL)
    {
        fprintf(out, "ошибка открытия файла");
        return -1;
    }

    fscanf(in, "%lf", &left);
    fscanf(in, "%lf", &right);

    check = checkForRoots(left, right);
    if (check == -2)
    {
        fprintf(out, "Корней нет");
        return -1;
    }
    if (check == -1)
    {
        x = left;
        fprintf(out, "x = %.8lf", x);
        return x;
    }
    if (check == 1)
    {
        x = right;
        fprintf(out, "x = %.8lf", x);
        return x;
    }

    do
    {
        x = findNextX(left, right);
        if ((checkForRoots(left, x) * checkForRoots(x, right)) == -1)
        {
            fprintf(out, "x = %.8lf", x);
            return x;
        }
        if (checkForRoots(left, x) == -2)
        {
            left = x;
        }
        else
        {
            right = x;
        }
    } while (fabs(right - left) > e);

    fprintf(out, "x = %.8lf", x);
    return x;
}