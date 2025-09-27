#include "Winged_Dragon/Filter.h"

// Ali-Wael
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
// Ali-Wael
void Filter::mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int startX, int startY) {
    double dx = (double) transpaerncy / 100;
    int w;
    int h;

    if(option == 1) {
        w = std::max(orig.width, merged.width);
        h = std::max(orig.height, merged.height);
        resizeImage(orig,w,h);
        resizeImage(merged,w,h);
    } else {
        w = std::min(orig.width - startX, merged.width);
        h = std::min(orig.height - startY, merged.height);
        cropImage(orig,{startX,startY}, {w,h});
        cropImage(merged,{0,0}, {w,h});
    }

    // create Temp image    
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
// amr atif
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
// Ali-Wael
void Filter::darkenLightn(Image &orig, int percent) { // Ali-Wael
    // percent -100 to 100
    double v = pow((double) std::abs(percent) / 100,1.5);
    
    bool dark = 0;
    if(percent < 0) dark = 1;
    
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                if(dark) orig(x,y,c) = std::max(0.0,(1-v) * orig(x,y,c));
                else orig(x,y,c) = std::min(255.0,(1+v) * orig(x,y,c));
            }
        }
    }
}
// amr atif
void  Filter::cropImage(Image  &orig, std::pair<int,int> st, std::pair<int,int> dimension) {
    Image temp(dimension.first, dimension.second); 
    for (int i = 0; i < dimension.first; i++) {           
        for (int j = 0; j < dimension.second; j++) {       
            for (int c = 0; c < orig.channels; c++) {
                temp(i, j, c) = orig(st.first + i, st.second + j, c);
            }
        }
    }
    orig = temp;
}

void Filter::addFrame(Image &orig, Image *frame) {

}
// Ali-Wael
void Filter::detectEdges(Image &orig, double alpha, int tresh) { // Ali-Wael
    grayScale(orig);
    if(alpha > 0.0) blurImage(orig, alpha,1);

    int w = orig.width;
    int h = orig.height;

    int g1[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}}; // horizontal
    int g2[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}}; // vertical

    double *arr = new double[w*h], mx = 0.0;

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            double sum1 = 0, sum2 = 0;
            
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    double val = orig(x + dx, y + dy, 0);
                    sum1 += val * g1[dy + 1][dx + 1];
                    sum2 += val * g2[dy + 1][dx + 1];
                }
            }
            
            double grad = sqrt(sum1 * sum1 + sum2 * sum2);

            arr[y * w + x] = grad;
        }
    }

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            int out = (arr[y * w + x] >= tresh? 0 : 255);
            for(int c = 0; c < orig.channels; ++c) {
                orig(x,y,c) = out;
            }
        }
    }

    delete [] arr;
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

void Filter::blurImage(Image &orig, double alpha, int size) {
    
}
// Ali-Wael
void Filter::contrast(Image &orig, int percent){ 
    double v = 1.0 + (double) percent / 100;
    if(percent >= 0) v = 1.0 + (double) percent / 100;
    else v = 1.0 + (double) percent / 200;
    
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                double val = (orig(x,y,c)-128.0) * v + 128.0;
                val = std::max(0.0,std::min(255.0,val));
                orig(x,y,c) = val;
            }
        }
    }
}