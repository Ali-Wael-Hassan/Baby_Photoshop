#include "Winged_Dragon/Filter.h"
#include <cmath>
#include <algorithm>


void Filter::grayScale(Image &orig) {
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            int R = orig(x,y,0),
                G = orig(x,y,1),
                B = orig(x,y,2);
            
            int gray= std::min(0.299*R+0.587*G+0.114*B + 0.5, 255.0);

            for(int c = 0; c < orig.channels; ++ c) {
                orig(x,y,c) = gray;
            }
        }
    }
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

void Filter::mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int startX, int startY) {
    // Contribution of Second Image
    double dx = (double) transpaerncy / 100;
    int w;
    int h;

    // define the Option 0: Resize with max h,w;
    //Option 1: crop and get the area with min h,w with starting point
    if(option) {
        w = std::max(orig.width, merged.width);
        h = std::max(orig.height, merged.height);
        resizeImage(orig,w,h);
        resizeImage(merged,w,h);
    } else {
        w = std::min(orig.width, merged.width);
        h = std::min(orig.height, merged.height);
        cropImage(orig,{startX,startY}, {w,h});
        cropImage(merged,{startX,startY}, {w,h});
    }

    // creat Temp image
    Image temp(w,h);

    for(int x = 0; x < w; ++x) {
        for(int y = 0; y < h; ++y) {
            for(int c = 0; c < temp.channels; ++c) {
                double val = (1-dx) * orig(x,y,c) + dx * merged(x,y,c);
                temp(x,y,c) = std::min(255.0, std::max(0.0,val));
            }
        }
    }

    orig = temp;
}

void Filter::flipImage(Image &orig, int option) {

}

void Filter::rotateImage(Image &orig, int degree) {

}

void Filter::darkenLightn(Image &orig, int percent) {
    // percent -100 to 100
    double v = pow((double) std::abs(percent) / 100,1.5);
    
    bool dark = 0;
    if(percent < 0) dark = 1;
    
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                if(dark) orig(x,y,c) = std::max(0.0,(1-v) * orig(x,y,c));
                else orig(x,y,c) = std::min(255.0,(1-v) * orig(x,y,c) + v * 255.0);
            }
        }
    }
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

void Filter::contrast(Image &orig, int percent){
    // percent -100 to 100
    double v = (double) percent / 100;
    
    bool dark = 0;
    if(percent < 0) dark = 1;
    
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                if(dark) orig(x,y,c) = std::max(0.0,(255-orig(x,y,c)) * v+ orig(x,y,c));
                else orig(x,y,c) = std::min(255.0,v *orig(x,y,c) + orig(x,y,c));
            }
        }
    }
}
