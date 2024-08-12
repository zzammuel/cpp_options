// #include <iostream>
// #include <cmath>

// using namespace std;

// template<typename F>
// double bisection(F func, double leftpoint, double rightpoint, double tol, int maxiter){
//     double midpoint;
//     double f_left, f_right, f_mid;

//     f_left = func(leftpoint);
//     f_right = func(rightpoint);

//     // If either function calls evaluate to 0, we have found our root.
//     if (f_left==0.0){return leftpoint;}
//     if (f_right==0.0){return rightpoint;}

//     // Ensure that the left point always evaluates to a negative sign
//     if (f_left>0.0){
//         double temp = rightpoint;
//         rightpoint = leftpoint;
//         leftpoint = temp;

//         temp = f_right;
//         f_right = f_left;
//         f_left = temp;
//     }

//     // If the signs are not opposite, we can't get closer to the root.
//     if ((f_left < 0.0) ^ (f_right > 0.0)){
//         cout << "f(a) and f(b) are not the same sign." << endl;
//         return 0.0;
//     }

//     // Calculate first midpoint
//     midpoint = (leftpoint+rightpoint) / 2.0;
//     f_mid = func(midpoint);
    
//     // Search for root until either tolerance is reached or the maximum amount of iterations is breached.
//     int it = 0;
//     while ((abs(f_mid) > tol) & (it < maxiter)){
//         if (f_mid > 0.0){
//             rightpoint = midpoint;
//         }
//         else{
//             leftpoint = midpoint;
//         }
//         midpoint = (leftpoint + rightpoint) / 2.0;
//         f_mid = func(midpoint);

//         it++;
//     }

//     return midpoint;
// };