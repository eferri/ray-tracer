#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define EPSILON 0.0001

#include <cmath>

namespace tracer{

// These functions implement relation operators using the EPSILON
// value to compare floating point values.
bool isEqual(double & a, double b) {
    return std::abs(a - b) < EPSILON;
}

bool isGreaterThan(double & a, double b) {
    return (std::abs(a - b) > EPSILON) && (a > b);
}

bool isLessThan(double & a, double b) {
    return (std::abs(a - b) > EPSILON) && (a < b);    
}

// Used to indicate if there was an intersection.
// If there was, opt is set to true and val contains the parametric
// point of intersection. If there was not, opt is false and val
// is undefined (0.0 by default).
class doubleOption {
public:
    double val;
    bool opt;

    doubleOption() {
        val = 0.0;
        opt = false;
    }
    
    doubleOption(double value) {
        val = value;
        opt = true;
    }
};

class Shape {};

}

#endif