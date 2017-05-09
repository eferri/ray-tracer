#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <cmath>
#include "Constants.hpp"


namespace tracer{

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

//Superclass for all shapes. Shapes must implement the hit method.
class Surface {
    virtual doubleOption hit(const Ray & ray) const = 0;
};

}

#endif