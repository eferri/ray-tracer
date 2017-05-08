#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <cmath>

#include "Geometry.hpp"
#include "Exceptions.hpp"

namespace tracer{

// Represents a sphere.
class Sphere : public Shape {
public:
    Sphere(const glm::dvec3 & origin, const double radius) {
        o = origin;
        r = radius;
    }

    glm::dvec3 origin() const {
        return o;
    }


    double radius() const {
        return r;
    }

    doubleOption intersect(const Ray & ray) const {
        double A = glm::dot(ray.direction(), ray.direction());
        glm::dvec3 dist = ray.origin() - o;
        double B = 2.0 * glm::dot(ray.direction(),dist);
        double C = glm::dot(dist,dist) - r*r;

        double disc = B*B - 4.0 * A * C;
        
        // Directly compare here to avoid taking the square root of a negative.
        if (disc < 0.0) {
            return doubleOption();
        }

        double root = std::sqrt(disc);
        double t1 = (-B + root) / (2*A);
        double t2 = (-B - root) / (2*A);
        
        if (isEqual(t1,t2)) {
            return doubleOption(t1);
        } else if (glm::distance(ray.pointAt(t1), ray.origin()) < glm::distance(ray.pointAt(t2), ray.origin())) {
            return doubleOption(t1);
        } else {
            return doubleOption(t2);
        }
    }

private:
    glm::dvec3 o;
    double r;    
};

class Plane: public Shape {
public:
    Plane(const glm::dvec3 & normal, const glm::dvec3 & point) {
        n = normal;
        p = point;
    }

    glm::dvec3 normal() const {
        return n;
    }


    glm::dvec3 point() const {
        return p;
    }

    doubleOption intersect(const Ray & ray) const {
        double denominator = dot(ray.direction(),n);
        double numerator = dot(p - ray.origin(),n);
        // Check possible intersection cases
        if (!isEqual(denominator, 0.0)) {
            return doubleOption(numerator / denominator);
        } else if (isEqual(numerator, 0.0)) {
            // Line is in plane. return dummy t value
            return doubleOption(1.0);;
        } else {
            return doubleOption();            
        }
    }
private:
    glm::dvec3 n;
    glm::dvec3 p;
};

}

#endif