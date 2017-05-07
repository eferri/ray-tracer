#include <iostream>

#include "../include/ImageWriter.hpp"
#include "../include/Exceptions.hpp"
#include "../include/RayTracer.hpp"

int main() {
    ImageWriter::ImageWriter h(250,250);
    ImageWriter::Pixel temp(100,255,100);
    for (int i = 0; i < h.height; i+=5) {
        for (int j = 0; j < h.width; j+=2) {
            h.writePixel(j,i,temp);
        }    
    }
    
    h.writeImage();
}