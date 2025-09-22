#include "header/Winged_Dragon/Filter.h"

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

}

void Filter::invertImage(Image &orig) {

}

void Filter::mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int startX = 0, int startY = 0) {
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
        cropImage(orig,{startX,startY}, {startX+w-1,startY+h-1});
        cropImage(merged,{startX,startY}, {startX+w-1,startY+h-1});
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
