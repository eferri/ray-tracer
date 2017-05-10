#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <cmath>
#include "Constants.hpp"
#include "Ray.hpp"

namespace tracer{

// Used to indicate if there was an intersection.
// If there was, opt is set to true and val contains the parametric
// point of intersection. If there was not, opt is false and val
// is undefined (0.0 by default). obj contains the index of the object
// of intersection, if it exists. obj must be set manually. 
class HitRecord {
public:
    double val;
    bool opt;
    int obj;

    HitRecord() {
        val = 0.0;
        opt = false;
        obj = 0;
    }
    
    HitRecord(double value) {
        val = value;
        opt = true;
        obj = 0;
    }
};

// Superclass for all surfaces. Surfaces must implement the hit method.
// Each surface instance also has a shade method, which uses the given material properties.
class Surface {
protected:
    glm::dvec3 specularConst;
    glm::dvec3 colourConst;
    double reflectConst;
public:
    
    glm::dvec3 specular() {return specularConst;}
    glm::dvec3 colour() {return colourConst;}
    double reflect() {return reflectConst;}    
    virtual HitRecord hit(Ray & ray) = 0;
    // Returns the normalized normal
    virtual glm::dvec3 normal(glm::dvec3 & point) = 0;
};

}

#endif