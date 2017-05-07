#include <iostream>

#include "ImageWriter.hpp"
#include "Exceptions.hpp"
#include "RayTracer.hpp"

int main() {
    ImageWriter::ImageWriter h(256,256);
    ImageWriter::Pixel temp(255,255,255);
    h.writePixel(128,128,temp);
    h.writeImage();
}