#include <iostream>
#include <cmath>

using namespace std;

template<typename F>
double bisection(F func, double leftpoint, double rightpoint, double tol = 1e-12, int maxiter = 100){
    double midpoint;
    double f_left, f_right, f_mid;

    f_left = func(leftpoint);
    f_right = func(rightpoint);

    if (f_left * f_right>=0)
    {
        cout << "f(a) and f(b) are not the same sign." << endl;
        return 0.0;
    }

    // Calculate first midpoint
    midpoint = (leftpoint+rightpoint) / 2.0;
    f_mid = func(midpoint);
    
    // Search for root until either tolerance is reached or the maximum amount of iterations is breached.
    int it = 0;
    while ((abs(f_mid) > tol) & (it < maxiter)){
        if (f_mid > 0.0){
            rightpoint = midpoint;
        }
        else{
            leftpoint = midpoint;
        }
        midpoint = (leftpoint + rightpoint) / 2.0;
        f_mid = func(midpoint);

        it++;
    }

    return midpoint;
};