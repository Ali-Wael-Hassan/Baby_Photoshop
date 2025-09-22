

#include "Winged_Dragon/Filter.h"



void Filter::grayScale(Image &orig) {
    
}

void Filter::blackWhite(Image &orig) {
    static const int bayer8[8][8] = {
        { 0, 32,  8, 40,  2, 34, 10, 42},
        {48, 16, 56, 24, 50, 18, 58, 26},
        {12, 44,  4, 36, 14, 46,  6, 38},
        {60, 28, 52, 20, 62, 30, 54, 22},
        { 3, 35, 11, 43,  1, 33,  9, 41},
        {51, 19, 59, 27, 49, 17, 57, 25},
        {15, 47,  7, 39, 13, 45,  5, 37},
        {63, 31, 55, 23, 61, 29, 53, 21}
    };
    const int N = 8;              
    const double scale = 255.0 / (N * N);

    for (int j = 0; j < orig.height; ++j) {
        for (int i = 0; i < orig.width; ++i) {
            
            double R = orig(i, j, 0);
            double G = orig(i, j, 1);
            double B = orig(i, j, 2);

            
            double lum = 0.2126 * R + 0.7152 * G + 0.0722 * B;
            int m = bayer8[j % N][i % N];
            double thresh = (m + 0.5) * scale; 

            int out = (lum >= thresh) ? 255 : 0;
            orig.setPixel(i, j, 0, out);
            orig.setPixel(i, j, 1, out);
            orig.setPixel(i, j, 2, out);
        }
    }
}


void Filter::invertImage(Image &orig) {

}

void Filter::mergeImage(Image &orig, int option, int transpaerncy) {

}

void Filter::flipImage(Image &orig, int option) {

}

void Filter::rotateImage(Image &orig, int degree) {

}

void Filter::darkenLightn(Image &orig, int percent) {

}

void Filter::cropImage(Image &orig, std::pair<int, int> st, std::pair<int, int> end) {

}

void Filter::addFrame(Image &orig, Image *frame) {

}

void Filter::detectEdges(Image &orig) {

}

void Filter::resizeImage(Image &orig, int width, int height) {

}

void Filter::blurImage(Image &orig, int radious) {
    
}
