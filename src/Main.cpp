#include <iostream>
#include <glm/vec3.hpp>

#include "../include/ImageWriter.hpp"
#include "../include/Exceptions.hpp"
#include "../include/Ray.hpp"
#include "../include/Shapes.hpp"
#include "../include/Geometry.hpp"


using namespace tracer;

glm::dvec3 shade(const Ray & ray, const Sphere & sphere, const Plane & plane) {
    
    
    doubleOption sphereIntersect = sphere.intersect(ray);
    doubleOption planeIntersect = plane.intersect(ray);

    if ((!planeIntersect.opt && !sphereIntersect.opt) || (planeIntersect.val < 0.0 && !sphereIntersect.opt)) {
        return glm::dvec3(0.2,0.2,0.2);
    } else if (sphereIntersect.opt) {
        return glm::dvec3(1.0,0.5,0.0);
    } else {
        return glm::dvec3(0.0,1.0,0.5);        
    }
}

int main() {
    ImageWriter image(1000,500);
    // orthonormal basis U,V,W of camera-screen system
    glm::dvec3 u(1.0,0.0,0.0);
    glm::dvec3 v(0.0,1.0,0.0);
    glm::dvec3 w(0.0,0.0,1.0);

    double screenWidth = 4.0;
    double screenHeight = 2.0;
    double screenDepth = 1.0;
    
    // Screen edge locations. Screen is positioned such that the
    // middle pixel is at the origin of the u-v plane. 
    double l = -screenWidth / 2.0;
    double b = -screenHeight / 2.0;
    
    // Origin is the camera position
    glm::dvec3 origin(0.0,0.0,0.0);
    glm::dvec3 light(2.0,5.0,0.0)
    // colour vector used for shading
    glm::dvec3 colour(0.0,0.0,0.0);
    Sphere sphere(glm::dvec3(0.0,0.0,-1.0), 0.5);
    Plane plane(v, -5.0*v);

    for(int j = 0; j < image.imgHeight(); j++) {
        for (int i = 0; i < image.imgWidth(); i++) {
            double x = l + screenWidth*(double(i) + 0.5) / double (image.imgWidth());
            double y = b + screenHeight*(double(j) + 0.5) / double (image.imgHeight());

            Ray ray(origin, -screenDepth*w + x*u + y*v);
            colour = shade(ray, sphere, plane);
            unsigned char r = (unsigned char) 255.9999 * colour.x;
            unsigned char g = (unsigned char) 255.9999 * colour.y;
            unsigned char b = (unsigned char) 255.9999 * colour.z;
            Pixel pix(r,g,b);
            image.writePixel(i,j,pix);
        }        
    }
    image.writeImage();
}