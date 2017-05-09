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

// Superclass for all surfaces. Surfaces must implement the hit method.
// Each surface instance also has a shade method, which uses the given material properties.
class Surface {
protected:
    double diffuseConst;
    double specularConst;
    glm::dvec3 colourConst;
public:
    double diffuse() {return this->diffuseConst;}
    double specular() {return this->specularConst;}
    glm::dvec3 colour() {return this->colourConst;}
    virtual doubleOption hit(Ray & ray) = 0;
    virtual glm::dvec3 normal() = 0;

    glm::dvec3 shadeObject(Ray & ray) {
        return glm::dvec3(0.0,0.0,0.0);
    }
};

}

#endif