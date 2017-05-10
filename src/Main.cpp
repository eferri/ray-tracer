#include <iostream>
#include <glm/vec3.hpp>
#include <cmath>

#include "../include/ImageWriter.hpp"
#include "../include/Ray.hpp"
#include "../include/Shapes.hpp"
#include "../include/Surface.hpp"
#include "../include/Geometry.hpp"
#include "../include/Constants.hpp"

using namespace tracer;

// Returns the a double option with the closest point of intersection.
// HitRecord.opt is false if no hit occured.
HitRecord QueryScene(Ray & ray, Surface **objList, int numObjs) {
    
    // Initialization is arbitrary since we will use the bool
    // from the HitRecord to indicate if we have had a hit or not
    HitRecord hitRec;
    double closestVal = T_1;
    bool hit = false;
    int obj = 0;

    for (int i = 0; i < numObjs; i++) {
        hitRec = objList[i]->hit(ray);
        if (hitRec.opt && (hitRec.val < closestVal)) {
            hit = true;
            closestVal = hitRec.val;
            obj = i;
        }
    }

    if (hit) {
        HitRecord result(closestVal);
        result.obj = obj;
        return result;
    } else {
        return HitRecord();
    }
}

glm::dvec3 shadeObject(Ray & ray, HitRecord hit, 
                       Surface ** objList, int numObjs) {
        
        Surface * obj = objList[hit.obj];
        glm::dvec3 light(AMBIENT_INTENSITY);
        light = light*obj->colour(); 
        
        glm::dvec3 point = ray.pointAt(hit.val);
        
        Ray lightRay(point, glm::dvec3(LIGHT_SOURCE) - point);
        
        // Send shadow feeler
        HitRecord lightHit = QueryScene(lightRay, objList, numObjs);
        // If we don't intersect anything, not in the shadow. Otherwise,
        // only light is ambient. 
        
        if (!lightHit.opt) {
            // Lambertian shading
            glm::dvec3 lightVal(LIGHT_INTENSITY);
            glm::dvec3 normalRayDirection = glm::normalize(lightRay.direction());

            double ndotL = glm::max(0.0, glm::dot(obj->normal(point), normalRayDirection));
            light = light + lightVal * obj->colour() * ndotL;

            // Specular (Blinn-Phong shading)
            glm::dvec3 half = glm::normalize(normalRayDirection - glm::normalize(ray.direction()));
            light = light + obj->specular() * light * glm::max(0.0, pow(glm::dot(obj->normal(point), half), 100.0));

        }
        return light;
}

// The render method finds the closest object and calls it's shade method.
glm::dvec3 Render(Ray & ray, Surface **objList, int numObjs) {
    HitRecord hit = QueryScene(ray,objList,numObjs);
    
    if (!hit.opt) {
        return glm::dvec3(BACKGROUND_COLOUR);
    }
    
    glm::dvec3 intensity = shadeObject(ray, hit, objList, numObjs);
    
    Surface * obj = objList[hit.obj];
    if (obj->reflect() > 0.0 && glm::length(intensity) > REFLECT_THRESHOLD) {
        glm::dvec3 rayDir = normalize(ray.direction());
        glm::dvec3 point = ray.pointAt(hit.val);
        glm::dvec3 normal = obj->normal(point);
        glm::dvec3 reflectDir = rayDir - 2*glm::dot(rayDir,normal)*normal;
        Ray reflectRay(point, reflectDir);
        intensity = intensity + obj->reflect()*Render(reflectRay, objList, numObjs);
    }
    return intensity;
}


int main() {
    ImageWriter image(IMAGE_WIDTH,IMAGE_HEIGHT);
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
    glm::dvec3 light(2.0,5.0,0.0);
    // colour vector used for shading
    glm::dvec3 colour(0.0,0.0,0.0);
    
    Surface **objList = new Surface *[NUM_SURFACES];
    
    Sphere sphere(ORIGIN_SPHERE, RADIUS_SPHERE, SPECULAR_SPHERE, COLOUR_SPHERE, REFLECT_SPHERE);
    Sphere sphere2(ORIGIN_SPHERE2, RADIUS_SPHERE2, SPECULAR_SPHERE2, COLOUR_SPHERE2, REFLECT_SPHERE2);    
    Plane plane(NORMAL_PLANE, POINT_PLANE, SPECULAR_PLANE, COLOUR_PLANE, REFLECT_PLANE);
    
    objList[0] = &sphere;
    objList[1] = &sphere2;    
    objList[2] = &plane;    

    for(int j = 0; j < image.imgHeight(); j++) {
        for (int i = 0; i < image.imgWidth(); i++) {
            
            for (int k = 0; k < 5; k++) {
                double x = l + screenWidth*(double(i) + 2 * randDouble() * 0.5) / double (image.imgWidth());
                double y = b + screenHeight*(double(j) + 2 * randDouble() * 0.5) / double (image.imgHeight());

                Ray ray(origin, -screenDepth*w + x*u + y*v);
                colour = colour + Render(ray, objList, NUM_SURFACES);
            }

            colour = colour / 5.0;

            unsigned char r = (unsigned char) 255.9999 * colour.x;
            unsigned char g = (unsigned char) 255.9999 * colour.y;
            unsigned char b = (unsigned char) 255.9999 * colour.z;
            Pixel pix(r,g,b);
            image.writePixel(i,j,pix);
        }        
    }
    image.writeImage();
}
