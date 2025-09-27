#include <cstdint>   
#include <algorithm> 
#include "Winged_Dragon/Filter.h"



void Filter::grayScale(Image &orig) {
    
}
// amr atif
void Filter::blackWhite(Image &orig) {
        Filter temp;
        temp.grayScale(orig);
        for(int i = 0;i<orig.width;i++){
            for(int j = 0;j<orig.height;j++){
                for(int c = 0;c<orig.channels;c++){
                    orig(i,j,c)=((orig(i,j,c)>=128)? 255:0);
                }
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
// amr atif
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
// amr atif
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
                
                int x0 = std::min(orig.width-1,std::max(0,x));
                int x1 = std::min(orig.width-1,std::max(0,x+1));
                int y0 = std::min(orig.height-1,std::max(0,y));
                int y1 = std::min(orig.height-1,std::max(0,y+1));
                double top = orig(x0, y0, c) * (1 - dx) + orig(x1, y0, c) * dx;
                double bottom = orig(x0, y1, c) * (1 - dx) + orig(x1, y1, c) * dx;
                double val = top * (1 - dy) + bottom * dy;

                temp(i, j, c) = static_cast<uint8_t>(std::min(255.0,std::max(0.0,val)));
            }
        }
    }

    orig = temp;
}



void Filter::blurImage(Image &orig, int radious) {
    
}
