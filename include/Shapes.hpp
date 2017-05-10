#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/common.hpp>
#include <cmath>

#include "Geometry.hpp"
#include "Surface.hpp"
#include "Ray.hpp"
#include "Constants.hpp"

namespace tracer{

// Represents a sphere.
class Sphere : public Surface {
public:
    Sphere(const glm::dvec3 & origin, const double & radius,
           const glm::dvec3 & specular, const glm::dvec3 & colour,
           const double & reflect) {
        
        o = origin;
        r = radius;
        specularConst = specular;
        colourConst = colour;
        reflectConst = reflect;        
    }

    glm::dvec3 origin() {
        return o;
    }


    double radius() {
        return r;
    }

    glm::dvec3 normal(glm::dvec3 & point) {
        return glm::normalize(point - o);
    }

    HitRecord hit(Ray & ray)  {
        double A = glm::dot(ray.direction(), ray.direction());
        glm::dvec3 dist = ray.origin() - o;
        double B = 2.0 * glm::dot(ray.direction(),dist);
        double C = glm::dot(dist,dist) - r*r;

        double disc = B*B - 4.0 * A * C;
        
        // Directly compare here to avoid taking the square root of a negative.
        if (disc < 0.0) {
            return HitRecord();
        }

        double root = std::sqrt(disc);
        double h1 = (-B + root) / (2*A);
        double h2 = (-B - root) / (2*A);        

        bool result1 = (h1 > T_0 && h1 < T_1);
        bool result2 = (h2 > T_0 && h2 < T_1);

        if (result1 && result2) {
            h1 = glm::min(h1,h2);
            return HitRecord(h1);
        } else if (result1) {
            return HitRecord(h1);
        } else if (result2) {
            return HitRecord(h2);
        } else {
            return HitRecord();
        }
    }

private:
    glm::dvec3 o;
    double r;
};

// Represents a plane
class Plane: public Surface {
public:
    Plane(const glm::dvec3 & normal, const glm::dvec3 & point,
          const glm::dvec3 & specular, const glm::dvec3 & colour,
          const double & reflect) {
        
        n = glm::normalize(normal);
        p = point;
        specularConst = specular;
        colourConst = colour;
        reflectConst = reflect;
    }

    glm::dvec3 normal(glm::dvec3 & point) {
        return n;
    }


    glm::dvec3 point() {
        return p;
    }

    HitRecord hit( Ray & ray) {
        double denominator = dot(ray.direction(),n);
        double numerator = dot(p - ray.origin(),n);
        // Check possible intersection cases
        if (!isEqual(denominator, 0.0)) {
            double result = (numerator / denominator);
            // Check to make sure result is in the valid intersect range
            if (result > T_0 && result < T_1) {
                return HitRecord(result);
            } else {
                return HitRecord();
            }            
        } else if (isEqual(numerator, 0.0)) {
            // Line is in plane. return dummy t value
            return HitRecord(1.0);;
        } else {
            return HitRecord();            
        }
    }
private:
    glm::dvec3 n;
    glm::dvec3 p;
};

}

#endif