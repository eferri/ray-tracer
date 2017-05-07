#include <iostream>
#include <fstream>
#include <vector>

#include "Exceptions.hpp"

namespace ImageWriter {

class Pixel {
public:
    Pixel(unsigned char red, unsigned char green, unsigned char blue) {
        R = red;
        G = green;
        B = blue;
    }

    Pixel() {
        R = 0;
        G = 0;
        B = 0;
    }
    unsigned char R, G, B;
};

class ImageWriter {
public:
   // Creates a blank image, with all pixels set to black (RGB value 0,0,0)
   // by default.
    ImageWriter(int imageWidth, int imageHeight)
        : image(imageWidth * imageHeight, Pixel())
    {
        width = imageWidth;
        height = imageHeight;        
    }

    void writePixel(int x, int y, Pixel &pix) {
        image.at(height * y + x) = pix;
    }

    // Writes the raster image information stored in imageWriter to a bitmap (bmp) file.
    // The data is uncompressed.
    void writeImage() {
        // Template bitmap file (bmp) headers. the actual values for the size fields are filled in below.
        // See https://en.wikipedia.org/wiki/BMP_file_format for more information.
        unsigned char fileHeader[14] = {0x42, 0x4D, 0,0,0,0, 0,0, 0,0, 54,0,0,0};
        // The rest of the bytes in the infoHeader default to 0 for uncompressed images.
        unsigned char infoHeader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
        unsigned char pix[3] = {0,0,0};
        unsigned char pad[2] = {0,0};

        // Fill in file size. Because of padding, every two 3-byte pixels takes 4-bytes of storage.

        int imageSize = image.size();
        std::cout << imageSize << std::endl;            

        int fileSize = 14 + 40 + imageSize + imageSize / 2;
        fileHeader[2] = (unsigned char) fileSize;
        fileHeader[3] = (unsigned char) fileSize>>8;
        fileHeader[4] = (unsigned char) fileSize>>16;
        fileHeader[5] = (unsigned char) fileSize>>24;                                        
        
        // Fill in dimensions of image
        infoHeader[4] = (unsigned char) width;
        infoHeader[5] = (unsigned char) width>>8;
        infoHeader[6] = (unsigned char) width>>16;
        infoHeader[7] = (unsigned char) width>>24;
        
        infoHeader[8] = (unsigned char) height;
        infoHeader[9] = (unsigned char) height>>8;
        infoHeader[10] = (unsigned char) height>>16;
        infoHeader[11] = (unsigned char) height>>24;
        
        std::ofstream outFile;
        outFile.open("out.bmp", std::ios::out | std::ios::binary);
        if (!outFile.is_open()) {
            throw CannotOpenFileException();
        }
        outFile.write((const char *) fileHeader, 14);
        outFile.write((const char *) infoHeader, 40);        
        
        for (int i = 0; i < imageSize; i++) {
            Pixel temp = image.at(i);
            pix[0] = temp.B;
            pix[1] = temp.G;
            pix[2] = temp.R;
            
            outFile.write((const char *) pix, 3);

            if (i % 2 == 1) {
                outFile.write((const char *) pad, 2);
            }
                        
        }
        outFile.close();
    }

private:
    std::vector<Pixel> image;
    int width;
    int height;
};

} // nameSpace ImageWriter