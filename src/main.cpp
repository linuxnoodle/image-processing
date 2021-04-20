#include <string>
#include <iostream>
#include <type_traits>
#include <vector>
#include <filesystem>

#include "../include/lodepng.hpp"
#include "../include/imageconverting.hpp"

#if defined (_WIN32)
    #include <windows.h>

    void clear(){
        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        if (hStdOut == INVALID_HANDLE_VALUE) return;

        if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
        cellCount = csbi.dwSize.X *csbi.dwSize.Y;

        if (!FillConsoleOutputCharacter(
            hStdOut,
            (TCHAR) ' ',
            cellCount,
            homeCoords,
            &count
        )) return;

        if (!FillConsoleOutputAttribute(
            hStdOut,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count
        )) return;

        SetConsoleCursorPosition( hStdOut, homeCoords );
    }

    void waitUntilNextFrame(int fps){
        Sleep(1000 * (float)1/fps);
    }
#elif defined(__unix__)
    #include <unistd.h>
    #include <term.h>

    void clear(){
        if (!cur_term){
            int result;
            setupterm( NULL, STDOUT_FILENO, &result );
            if (result <= 0) return;
        }

        putp(tigetstr("clear"));
    }

    void waitUntilNextFrame(int fps){
        usleep(1000000 * (float)1/fps);
    }
#endif

int main(){
    char *imagesFolder = (char*)"images";
    char *imagesPrefix = (char*)"bad-apple-";
    int imageCount = 0;

    for (const auto & image : std::filesystem::directory_iterator(imagesFolder))
        ++imageCount;
    
    for (int i = 1; i < imageCount; ++i){
        // Loads "image.png" into imageData, as well as defining it's width and height
        std::vector<unsigned char> imageData;
        unsigned int width, height, error;

        std::string currentName = std::string(imagesFolder) + "/" + imagesPrefix + std::to_string(i) + ".png";
        error = lodepng::decode(imageData, width, height, currentName.c_str());

        if (error){
            std::cout << "Image decoding error \"" << error << "\": " << lodepng_error_text(error) << "\n";
            return 1;
        }

        imageData = convertImageToBlackAndWhite(imageData, 220, 220, 220);

        std::string ascii;
        for (unsigned long int i = 0; i < imageData.size(); i += 4){
            if ((int)imageData[i] == 255){
                ascii += " ";
            } else {
                ascii += "#";
            }
            
            if ((i + 4) / 4 % (int)width == 0){
                ascii += "\n";
            }
        }
        
        clear();
        std::cout << ascii << "\n";
        waitUntilNextFrame(24);
    }

    return 0;
}
