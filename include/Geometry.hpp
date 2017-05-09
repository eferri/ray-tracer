#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "Constants.hpp"

//This file defines various mathmatical functions not related to any class.

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

double randDouble() {
    return double(rand()) / RAND_MAX;
}

}

#endif