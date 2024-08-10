#include <cmath>

double normalCDF(double value)
{
    return 0.5 * erfc(-value * M_SQRT1_2);
}

double normalPDF(double value)
{
    return exp(-value * value / 2) / sqrt(2 * M_PI);
}