#include <cstdint>   
#include <algorithm> 
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

void Filter::flipImage(Image &orig, bool& horiz) {
int l = 0;
    int r = (horiz) ? (orig.width - 1) : (orig.height - 1);
    int direction = (horiz) ? orig.height : orig.width;

    while (l < r) {
        for (int i = 0; i < direction; i++) {
            for (int c = 0; c < orig.channels; c++) {
                if (horiz)
                    std::swap(orig(l, i, c), orig(r, i, c));
                else
                    std::swap(orig(i, l, c), orig(i, r, c));
            }
        }
        l++;
        r--;
    }
}

void Filter::rotateImage(Image &orig, int degree) {

}

void Filter::darkenLightn(Image &orig, int percent) {

}

void  Filter::cropImage(Image  &orig, std::pair<int,int> st, std::pair<int,int> end) {
    Image temp(end.first, end.second); 
    for (int i =0; i < end.first; i++) {           
        for (int j = 0; j < end.second; j++) {       
            for (int c = 0; c < orig.channels; c++) {
                temp(i, j, c) = orig(st.first + i-1, st.second + j-1, c);
            }
        }
    }
    orig = temp;
}



void Filter::addFrame(Image &orig, Image *frame) {

}

void Filter::detectEdges(Image &orig) {

}

void Filter::resizeImage(Image &orig, int width, int height) {
    Image temp(width, height);
    double sw = static_cast<double>(orig.width) / width;
    double sh = static_cast<double>(orig.height) / height;

    for (int j = 0; j < height; j++) {
        double sy = j * sh;
        int y = static_cast<int>(sy);
        double dy = sy - y;

        for (int i = 0; i < width; i++) {
            double sx = i * sw;
            int x = static_cast<int>(sx);
            double dx = sx - x;

            for (int c = 0; c < orig.channels; c++) {

                int x0 = std::clamp(x, 0, orig.width - 1);
                int x1 = std::clamp(x + 1, 0, orig.width - 1);
                int y0 = std::clamp(y, 0, orig.height - 1);
                int y1 = std::clamp(y + 1, 0, orig.height - 1);

                double top = orig(x0, y0, c) * (1 - dx) + orig(x1, y0, c) * dx;
                double bottom = orig(x0, y1, c) * (1 - dx) + orig(x1, y1, c) * dx;
                double val = top * (1 - dy) + bottom * dy;

                temp(i, j, c) = static_cast<uint8_t>(std::clamp(val, 0.0, 255.0));
            }
        }
    }

    orig = temp;
}



void Filter::blurImage(Image &orig, int radious) {
    
}
