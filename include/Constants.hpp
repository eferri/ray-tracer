#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define EPSILON 0.0001

#define T_0 0.005
#define T_1 100.0
#define NUM_SURFACES 2
#define BACKGROUND_COLOUR glm::dvec3(0.1,0.1,0.1)

#define AMBIENT_INTENSITY 0.3,0.3,0.3
#define LIGHT_INTENSITY glm::dvec3(0.8,0.8,0.8)
#define LIGHT_SOURCE 5.0,8.0,4.0

// For Sphere
#define SPECULAR_SPHERE glm::dvec3(0.5,0.1,0.0)
#define COLOUR_SPHERE glm::dvec3(0.5,0.1,0.0)
#define ORIGIN_SPHERE glm::dvec3(0.0,0.0,-2.0)
#define RADIUS_SPHERE -0.5

// For Plane
#define SPECULAR_PLANE glm::dvec3(0.0,0.1,0.5)
#define COLOUR_PLANE glm::dvec3(0.0,0.1,0.5)
#define NORMAL_PLANE glm::dvec3(0.0,1.0,0.0)
#define POINT_PLANE glm::dvec3(0.0,-0.8,0.0)

#endif