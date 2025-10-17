#include "transformoperations.h"

// Ali Wael 20240354
void TransformOperations::mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int x1, int y1, int x2, int y2, int w, int h) {
    float dx = (float) transpaerncy / 100;

    if(option == 1) {
        w = std::max(orig.width, merged.width);
        h = std::max(orig.height, merged.height);
        resizeImage(orig,w,h);
        resizeImage(merged,w,h);
    } else {
        cropImage(orig,{x1,y1}, {w,h});
        cropImage(merged,{x2,y2}, {w,h});
    }

    // create Temp image
    Image temp(w,h);

    for(int x = 0; x < w; ++x) {
        for(int y = 0; y < h; ++y) {
            for(int c = 0; c < temp.channels; ++c) {
                float val = (1-dx) * orig(x,y,c) + dx * merged(x,y,c);
                temp(x,y,c) = std::min(255.0f, std::max(0.0f,val));
            }
        }
    }

    std::swap(orig,temp);
}

// Amr Atif 20240398
void TransformOperations::flipImage(Image &orig, bool& horiz) {
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


//Youssef Mohamed Hassib 20240707
void TransformOperations::rotateImage(Image &orig, int degree) {
    int n = degree / 90; // dependent on degree % 90 == 0, further updates to come to make it valid all 360 degrees
    while (n--) {
        Image res(orig.height, orig.width);
        for (int y = 0; y < orig.height; ++y) {
            for (int x = 0; x < orig.width; ++x) {
                for (int c = 0; c < orig.channels; ++c) {
                    res(orig.height - 1 - y, x, c) = orig(x, y, c);
                }
            }
        }
        std::swap(orig,res);
    }

}

// Amr Atif 20240398
void  TransformOperations::cropImage(Image  &orig, std::pair<int,int> st, std::pair<int,int> dimension) {
    Image temp(dimension.first, dimension.second);
    for (int i = 0; i < std::min(orig.width,dimension.first); i++) {
        for (int j = 0; j < std::min(orig.height,dimension.second); j++) {
            for (int c = 0; c < orig.channels; c++) {
                temp(i, j, c) = orig(std::min(orig.width - 1,std::max(0,st.first + i)), std::min(orig.height - 1, std::max(0,st.second + j)), c);
            }
        }
    }
    std::swap(orig,temp);
}

// Amr Atif 20240398
void TransformOperations::resizeImage(Image &orig, int width, int height) {
    Image temp(width, height);
    float sw = static_cast<float>(orig.width) / width;
    float sh = static_cast<float>(orig.height) / height;

    for (int j = 0; j < height; j++) {
        float sy = j * sh;
        int y = static_cast<int>(sy);
        float dy = sy - y;

        for (int i = 0; i < width; i++) {
            float sx = i * sw;
            int x = static_cast<int>(sx);
            float dx = sx - x;

            for (int c = 0; c < orig.channels; c++) {

                int x0 = std::min(orig.width-1,std::max(0,x));
                int x1 = std::min(orig.width-1,std::max(0,x+1));
                int y0 = std::min(orig.height-1,std::max(0,y));
                int y1 = std::min(orig.height-1,std::max(0,y+1));
                float top = orig(x0, y0, c) * (1 - dx) + orig(x1, y0, c) * dx;
                float bottom = orig(x0, y1, c) * (1 - dx) + orig(x1, y1, c) * dx;
                float val = top * (1 - dy) + bottom * dy;

                temp(i, j, c) = std::min(255.0f,std::max(0.0f,val));
            }
        }
    }

    std::swap(orig,temp);
}

// Ali Wael 20240354
void TransformOperations::skew(Image &orig, float rad)
{
    int offset = ceil(fabs(tan(rad) * orig.height));
    int w = orig.width + abs(offset);
    int h = orig.height;

    Image temp(w, h);
    std::fill(temp.imageData, temp.imageData + w * h * temp.channels, 45);

    for (int y = 0; y < h; ++y) {
        float ratio = (float) y / (h - 1);
        int shift = std::ceil(offset * (1.0f - ratio));

        for (int x = 0; x < orig.width; ++x) {
            int nx = x + shift;
            if (nx >= 0 && nx < w) {
                for (int c = 0; c < orig.channels; ++c)
                    temp(nx, y, c) = orig(x, y, c);
            }
        }
    }

    std::swap(temp, orig);
}
