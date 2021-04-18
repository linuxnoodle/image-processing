#include <iostream>
#include <vector>

#include "../include/lodepng.hpp"
#include "../include/imageconverting.hpp"

int main(){
    const char *fileName = "image.png";

    // Loads "image.png" into imageData, as well as defining it's width and height
    std::vector<unsigned char> imageData;
    unsigned int width, height, error;
    error = lodepng::decode(imageData, width, height, fileName);

    if (error){
        std::cout << "Image decoding error \"" << error << "\": " << lodepng_error_text(error) << "\n";
        return 1;
    }

    //error = lodepng::encode("bw.png", convertImageToBlackAndWhite(imageData, 244, 244, 244), width, height);
    std::vector<unsigned char> resizedImage = resizeImage(imageData, width, height, 50, 50);

    error = lodepng::encode("resized.png", resizedImage, 50, 50);
    
    if (error){
        std::cout << "Image encoding error \"" << error << "\": " << lodepng_error_text(error) << "\n";
        return 1;
    }
}
