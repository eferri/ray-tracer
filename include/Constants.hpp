#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define EPSILON 0.0001

#define IMAGE_WIDTH 1500
#define IMAGE_HEIGHT 750

#define T_0 0.00000001
#define T_1 1000.0
#define NUM_SURFACES 3
#define REFLECT_THRESHOLD 0.05
#define BACKGROUND_COLOUR 0.1,0.1,0.1

#define AMBIENT_INTENSITY 0.3,0.3,0.3
#define LIGHT_INTENSITY 0.5,0.5,0.5
#define LIGHT_SOURCE 3.0,3.0,2.0

// For Sphere
#define SPECULAR_SPHERE glm::dvec3(0.8,0.8,0.8)
#define COLOUR_SPHERE glm::dvec3(0.1,0.2,0.6)
#define ORIGIN_SPHERE glm::dvec3(1.4,0.0,-2.0)
#define RADIUS_SPHERE 0.5
#define REFLECT_SPHERE 0.001

#define SPECULAR_SPHERE2 glm::dvec3(0.7,0.7,0.7)
#define COLOUR_SPHERE2 glm::dvec3(0.5,0.3,0.3)
#define ORIGIN_SPHERE2 glm::dvec3(-1.8,0.5,-3.0)
#define RADIUS_SPHERE2 0.8
#define REFLECT_SPHERE2 0.8


// For Plane
#define SPECULAR_PLANE glm::dvec3(0.9,0.9,0.9)
#define COLOUR_PLANE glm::dvec3(0.3,0.3,0.3)
#define NORMAL_PLANE glm::dvec3(0.0,1.0,0.0)
#define POINT_PLANE glm::dvec3(0.0,-0.5,0.0)
#define REFLECT_PLANE 0.15

#endif