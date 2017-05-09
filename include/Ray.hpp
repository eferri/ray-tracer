#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include <glm/vec3.hpp>

namespace tracer{

class Ray {
public:
    Ray(const glm::dvec3 & origin, const glm::dvec3 & direction) {
        o = origin;
        d = direction;
    }

    glm::dvec3 origin() const {
        return o;
    }

    glm::dvec3 direction() const {
        return d;
    }

    glm::dvec3 pointAt(double t) const {
        return o + t*d;
    }
private:
    glm::dvec3 o;
    glm::dvec3 d;    
};

}

#endif