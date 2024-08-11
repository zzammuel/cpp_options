template<typename F>
double bisection(const F &func, double leftpoint, double rightpoint, double tol = 1e-12, int maxiter = 100);