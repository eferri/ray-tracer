#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define EPSILON 0.0001

#define IMAGE_WIDTH 4000
#define IMAGE_HEIGHT 2000

#define T_0 0.00000001
#define T_1 1000.0
#define NUM_SURFACES 3
#define REFLECT_THRESHOLD 0.05
#define RAND_SCATTER 0.02

#define BACKGROUND_COLOUR 0.5,0.5,0.5

#define AMBIENT_INTENSITY 0.0,0.0,0.0
#define LIGHT_INTENSITY 0.4,0.4,0.4
#define LIGHT_SOURCE -3.0,4.0,1.0

// For Sphere
#define SPECULAR_SPHERE glm::dvec3(0.0,0.0,0.0)
#define COLOUR_SPHERE glm::dvec3(0.1,0.1,0.1)
#define ORIGIN_SPHERE glm::dvec3(1.4,0.0,-1.0)
#define RADIUS_SPHERE 0.5
#define REFLECT_SPHERE 0.99

#define SPECULAR_SPHERE2 glm::dvec3(0.0,0.0,0.0)
#define COLOUR_SPHERE2 glm::dvec3(0.1,0.1,0.1)
#define ORIGIN_SPHERE2 glm::dvec3(-1.8,0.5,-1.7)
#define RADIUS_SPHERE2 0.8
#define REFLECT_SPHERE2 0.99


// For Plane
#define SPECULAR_PLANE glm::dvec3(0.0,0.0,0.0)
#define COLOUR_PLANE glm::dvec3(0.3,0.3,0.3)
#define NORMAL_PLANE glm::dvec3(0.0,1.0,0.0)
#define POINT_PLANE glm::dvec3(0.0,-0.5,0.0)
#define REFLECT_PLANE 0.0

#endif