#include <boost/math/special_functions/bessel.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>

// Bisection method to find the root
double findLambda(double r, double tol = 1e-6, double max_iter = 100) {
    double low = 0.01, up = 10.0;
    double mid;
    int iter = 0;
    while (iter < max_iter) {
        mid = (low + up) / 2.0;
        double f_mid = boost::math::cyl_bessel_i(1, mid) / boost::math::cyl_bessel_i(0, mid) - r;
        if (std::abs(f_mid) < tol) {
            return mid;
        }
        double f_lower = boost::math::cyl_bessel_i(1, low) / boost::math::cyl_bessel_i(0, low) - r;
        if (f_lower * f_mid < 0) {
            up = mid;
        } else {
            low = mid;
        }
        iter++;
    }
    return mid;
}

int main() {
    double r = 0.5;
    try {
        double lambda = findLambda(r);
        std::cout << std::fixed << std::setprecision(12); // Set precision to 6 decimal places
        std::cout << "λ = " << lambda << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
