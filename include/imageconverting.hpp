#pragma once
#include <vector>
#include <stdexcept>
#include <cmath>

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
std::vector<unsigned char> convertImageToBlackAndWhite(std::vector<unsigned char> imageData, int redFilter = 0, int greenFilter = 0, int blueFilter = 0);

/**
 * Takes a lodepng image and squashes it down to a desired size.
 * Will error if:
 * - width less than or equal to 0
 * - height less than or equal to 0
 * - width and height don't match image data given
 *
 * @param imageData Lodepng image data
 * @param width Width of image data
 * @param height Height of image data
 * @param desiredWidth Output image width
 * @param desiredHeight Output image height
 * @return New resized array
 */
std::vector<unsigned char> resizeImage(std::vector<unsigned char> imageData, int width, int height, int desiredWidth, int desiredHeight);
