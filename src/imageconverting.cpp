#include "../include/imageconverting.hpp"
#include <stdexcept>

int getIndex(int w, int h, int stride){
    return h * stride + w;
}

/**
 * Converts a lodepng image to black and white.
 * If you don't supply the filter values, the default is 0.
 *
 * @param imageData Lodepng image data
 * @param (optional) redFilter If a pixel's red value is greater than this, that pixel will become white
 * @param (optional) greenFilter If a pixel's green value is greater than this, that pixel will become white
 * @param (optional) blueFilter If a pixel's blue value is greater than this, that pixel will become white
 * @return New array that is in black and white
 */
 std::vector<unsigned char> convertImageToBlackAndWhite(std::vector<unsigned char> imageData, int redFilter, int greenFilter, int blueFilter){
    for (unsigned long int i = 0; i < imageData.size(); i += 4){
        if (imageData[i] > redFilter || imageData[i + 1] > greenFilter || imageData[i + 2] > blueFilter){
            imageData[i] = 255;
            imageData[i + 1] = 255;
            imageData[i + 2] = 255;
            imageData[i + 3] = 255;
        } else {
            imageData[i] = 0;
            imageData[i + 1] = 0;
            imageData[i + 2] = 0;
            imageData[i + 3] = 255;
        }
    }
    return imageData;
}

/**
 * Takes a lodepng image and will downscale it to a desired size.
 * Will error if:
 * - width/height isn't evenly divisible by desiredWidth/desiredHeight
 * - desiredWidth/desiredHeight is greater than or equal to width/height
 * - width and height don't match image data given
 *
 * @param imageData Lodepng image data
 * @param width Width of image data
 * @param height Height of image data
 * @param desiredWidth Output image width
 * @param desiredHeight Output image height
 * @return New resized array
 */
std::vector<unsigned char> downscaleImage(std::vector<unsigned char> imageData, int width, int height, int desiredWidth, int desiredHeight){
    if (desiredWidth >= width || desiredHeight <= height){
        throw std::invalid_argument("desiredWidth/desiredHeight greater than or equal to width/height.");
    } else if (imageData.size() != 4 * width * height) {
        throw std::invalid_argument("Given width and height don't match imageData.");
    } else if (width % desiredWidth != 0 || height % desiredHeight != 0){
        throw std::invalid_argument("width/height is not divisible by desiredWidth/desiredHeight.");
    }
    
    std::vector<unsigned char> downscaledImage;
    downscaledImage.resize(desiredHeight * desiredWidth);

    int jump = 1;

    for (unsigned long int i = 0; i < imageData.size(); i += (4 * jump)){
         
    }
    return downscaledImage;
}

// Attempted to implement nearest neighbor scaling. Failed.
/*std::vector<unsigned char> resizeImage(std::vector<unsigned char> imageData, int width, int height, int desiredWidth, int desiredHeight){
    if (width <= 0|| height <= 0){
        throw std::invalid_argument("Width/Height less than or equal to zero.");  
        return imageData;
    } else if (imageData.size() != 4 * width * height){
        throw std::invalid_argument("Given width and height don't match image.");
        return imageData;
    }

    std::vector<unsigned char> resizedImage;
    resizedImage.resize(desiredHeight * desiredWidth);
    int positionOfClostestX, positionOfClostestY;

    float widthScale = (float)width/desiredWidth, heightScale = (float)height/desiredHeight;
    
    for (int i = 0; i < desiredHeight; ++i){
        positionOfClostestY = (int)(heightScale * i + 0.5);
        for (int j = 0; j < desiredWidth; ++j){
            positionOfClostestX = (int)(widthScale * j + 0.5);
            
            int originalIndex = getIndex(positionOfClostestX, positionOfClostestY, width);
            int scaledIndex = getIndex(j, i, desiredWidth); 

            resizedImage[4 * originalIndex] = imageData[4 * scaledIndex];
            resizedImage[4 * originalIndex + 1] = imageData[4 * scaledIndex + 1];
            resizedImage[4 * originalIndex + 2] = imageData[4 * scaledIndex + 2];
            resizedImage[4 * originalIndex + 3] = 255;
        }
    }

    return resizedImage;
}*/

// Attempted to implement bilinear interpolation. Failed. 
/*std::vector<unsigned char> resizeImage(std::vector<unsigned char> imageData, int width, int height, int desiredWidth, int desiredHeight){
    if (width <= 0|| height <= 0){
        throw std::invalid_argument("Width/Height less than or equal to zero.");  
        return imageData;
    } else if (imageData.size() != 4 * width * height){
        throw std::invalid_argument("Given width and height don't match image.");
        return imageData;
    }

    std::vector<unsigned char> resizedImage;

    // Basically stole this implementation from https://tech-algorithm.com/articles/bilinear-image-scaling/
    int a, b, c, d, x, y, index, offset = 0;
    float widthRatio = (float)(width - 1)/desiredWidth;
    float heightRatio = (float)(height - 1)/desiredHeight;
    float xDifference, yDifference, blue, red, green;

    for (size_t i = 0; i < desiredHeight; ++i){
        for (size_t j = 0; j < desiredWidth; ++j){
            x = (int)(widthRatio * j);
            y = (int)(heightRatio * i);

            xDifference = (widthRatio * j) - x;
            yDifference = (heightRatio * i) - y;

            index = y * width + x;

            a = imageData[index];
            b = imageData[index + 1];
            c = imageData[index + width];
            d = imageData[index + width + 1];

            // Literally have no clue how this part works, gonna assume black magic.
            
            // Yb = Ab(1-w)(1-h) + Bb(w)(1-h) + Cb(h)(1-w) + Db(wh)
            blue = (a & 0xff) * (1 - widthRatio) * (1 - heightRatio) + (b & 0xff) * (widthRatio) * (1 - heightRatio) + (c & 0xff) * (heightRatio) * (1 - widthRatio) + (d & 0xff) * (widthRatio * heightRatio);
            
            // Yg = Ag(1-w)(1-h) + Bg(w)(1-h) + Cg(h)(1-w) + Dg(wh)
            green = ((a >> 8) & 0xff) * (1 - widthRatio) * (1 - heightRatio) + ((b >> 8) & 0xff) * (widthRatio) * (1 - heightRatio) + ((c >> 8) & 0xff) * (heightRatio) * (1 - widthRatio) + ((d >> 8) & 0xff) * (widthRatio * heightRatio);
            
            // Yr = Ar(1-w)(1-h) + Br(w)(1-h) + Cr(h)(1-w) + Dr(wh)
            red = ((a >> 16) & 0xff) * (1 - widthRatio) * (1 - heightRatio) + ((b >> 16) & 0xff) * (widthRatio) * (1 - heightRatio) + ((c >> 16) & 0xff) * (heightRatio) * (1 - widthRatio)   + ((d >> 16) & 0xff) * (widthRatio * heightRatio);
        
            resizedImage[4 * y * desiredHeight + 4 * x] = red;
            resizedImage[4 * y * desiredHeight + 4 * x + 1] = green;
            resizedImage[4 * y * desiredHeight + 4 * x + 2] = blue;
            resizedImage[4 * y * desiredHeight + 4 * x + 3] = 255;
        }
    }

    return resizedImage;
}*/
