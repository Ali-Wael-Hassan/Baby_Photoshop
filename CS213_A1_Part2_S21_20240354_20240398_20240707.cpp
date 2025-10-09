/*
    Project : Baby Photoshop
    File    : CS213_A1_Part2_S21_20240354_20240398_20240707.cpp
    Section : S21

    Team Members:
    - Ali Wael       (ID 20240354)  -> Gray Scale (1), Merge Image (4), Darken & Lighten (7), Detect Edges (10)
    - Amr Atif       (ID 20240398)  -> Black & White (2), Flip Image (5), Crop Image (8), Resize Image (11)
    - Yousef Hassib  (ID 20240707)  -> Invert Colors (3), Rotate Image (6), Add Frame (10), Blur Image (12)
    Bonus:
    - Ali Wael       (ID 20240354)  -> Oil Painting, Skew Image
    - Amr Atif       (ID 20240398)  -> Purple Image, Infrared
    - Yousef Hassib  (ID 20240707)  -> Sun, Old TV

    WARNING:
        you must make image folder to run the program correctly

    Description:
    The program starts with the main menu which has two options:
        1) Load Image
        2) Exit

    After loading the first image, the Filter Menu appears:
        == File Options == 
            - Save image
            - Load new image
            - Back to main menu
        == Filters ==
            - All filters listed above

    First Note: darkenLight is Darken and Lighten combined: 
          (-v) applies Darken and (+v) applies Lighten.
    
    Second Note: images must be put in folder in the main directory with name image example: image/myImg.jpg
    Third Note: put only name of the image + extension
*/

#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <iostream>
#include <exception>
#include <limits>
#include <string>
#include <iomanip>
#include <stack>
#include <climits>

using namespace std;

#define vf vector<float>
#define vvf vector<vector<float>>

using namespace std;

class ToneAndColorAdjustments{
public:
    ToneAndColorAdjustments() = default;
    ~ToneAndColorAdjustments() = default;

    void grayScale(Image &orig);
    void blackWhite(Image &orig);
    void invertImage(Image &orig);
    void darkenLightn(Image &orig, int percent);
    void contrast(Image &orig, int percent);
    void purbleFilter(Image &orig);
    void infraredFilter(Image &orig,float percent);
    void sun(Image& orig, int percent);
    void tv(Image& orig);
};

// Ali Wael 20240354
void ToneAndColorAdjustments::grayScale(Image &orig) {
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            int R = orig(x,y,0),
                G = orig(x,y,1),
                B = orig(x,y,2);
            
            int gray= min(0.299f*R+0.587f*G+0.114f*B + 0.5f, 255.0f);

            for(int c = 0; c < orig.channels; ++ c) {
                orig(x,y,c) = gray;

            }
        }
    }
}

// Amr Atif 20240398
void ToneAndColorAdjustments::blackWhite(Image &orig) {
    grayScale(orig);
    for(int i = 0;i<orig.width;i++){
        for(int j = 0;j<orig.height;j++){
            for(int c = 0;c<orig.channels;c++){
                orig(i,j,c)=((orig(i,j,c)>=128)? 255:0);
            }
        }
    }
}

// Youssef Mohamed Hassib 20240707
void ToneAndColorAdjustments::invertImage(Image &orig) {
    for (int i = 0; i < orig.width; ++i) {
        for (int j = 0; j < orig.height; ++j) {
            orig(i, j, 0) = 255 - orig(i, j, 0);
            orig(i, j, 1) = 255 - orig(i, j, 1);
            orig(i, j, 2) = 255 - orig(i, j, 2);
        }
    }
}


//Ali Wael 20240354
void ToneAndColorAdjustments::darkenLightn(Image &orig, int percent) {
    // percent -100 to 100
    float v = pow((float) std::abs(percent) / 100,1.5);
    
    bool dark = 0;
    if(percent < 0) dark = 1;
    
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                if(dark) orig(x,y,c) = max(0.0f,(1-v) * orig(x,y,c));
                else orig(x,y,c) = min(255.0f,(1+v) * orig(x,y,c));
            }
        }
    }
}

// Ali Wael 20240354
void ToneAndColorAdjustments::contrast(Image &orig, int percent){ 
    // -100 to 100
    float v = 1.0f + (float) percent / 100;
    if(percent >= 0) v = 1.0f + (float) percent / 100;
    else v = 1.0f + (float) percent / 200;
    
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                float val = (orig(x,y,c)-128.0f) * v + 128.0f;
                val = max(0.0f,min(255.0f,val));
                orig(x,y,c) = val;
            }
        }
    }
}
// Amr Atif 20240398
void ToneAndColorAdjustments::purbleFilter(Image &orig)
{
    for (int i = 0; i < orig.width; i++) {
        for (int j = 0; j < orig.height; j++) {

            float R_new =min(max(orig(i, j, 0) * 1.2 + 10.0, 0.0), 255.0);
            float G_new =min(max(orig(i, j, 1) * 0.8 - 10.0, 0.0), 255.0);
            float B_new =min(max(orig(i, j, 2) * 1.3 + 20.0, 0.0), 255.0);

            orig(i, j, 0) = static_cast<unsigned char>(R_new);
            orig(i, j, 1) = static_cast<unsigned char>(G_new);
            orig(i, j, 2) = static_cast<unsigned char>(B_new);
        }
    }
}
// Amr Atif 20240398
void ToneAndColorAdjustments::infraredFilter(Image &orig,float precent =0)
{
    grayScale(orig);
    invertImage(orig);

    for (int y = 0; y < orig.height; ++y)
        for (int x = 0; x < orig.width; ++x) {
            orig(x, y, 1) = orig(x,y,0);               
            orig(x, y, 2) = orig(x,y,0);               
            orig(x,y,0) = 255;
        }
}
// Youssef Mohamed Hassib 20240707
void ToneAndColorAdjustments::sun(Image &orig, int percent) {

    float intensity = (float) percent / 100;
    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            float avg = 0.0;
            for (int i = 0; i < 3; ++i) {
                avg += orig(x, y, i);
            }
            avg /= 3;

            float ry = min(avg * 1.95, 255.0);
            float gy = min(avg * 1.80, 255.0);
            float by = min(avg * 0.85, 255.0);

            float r = orig(x, y, 0) * (1 - intensity) + ry * intensity;
            float g = orig(x, y, 1) * (1 - intensity) + gy * intensity;
            float b = orig(x, y, 2) * (1 - intensity) + by * intensity;

            orig(x, y, 0) = min(255.0f, max(r, 0.0f));
            orig(x, y, 1) = min(255.0f, max(g, 0.0f));
            orig(x, y, 2) = min(255.0f, max(b, 0.0f));


        }
    }
}
// Youssef Mohamed Hassib 20240707
void ToneAndColorAdjustments::tv(Image &orig) {
    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            if (y % 2) {
                for (int k = 0; k < 3; ++k) {
                    float val = orig(x, y, k) - orig(x, y, k) * 0.4;
                    orig(x, y, k) = min(255.0f, max(0.0f, val));

                }
            }
        }
    }
}
//===========================================================================================================================

class TransformOperations{
public:
    TransformOperations() = default;
    ~TransformOperations() = default;

    void mergeImage(Image &orig, Image &merged, int option, int transparency, int startX, int startY);
    void flipImage(Image &orig, bool& horiz);
    void rotateImage(Image &orig, int degree);
    void cropImage(Image  &orig, pair<int,int> st, pair<int,int> dimension);
    void resizeImage(Image &orig, int width, int height);
    void skew(Image &orig, float rad);
};

// Ali Wael 20240354
void TransformOperations::mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int startX, int startY) {
    float dx = (float) transpaerncy / 100;
    int w;
    int h;

    if(option == 1) {
        w = max(orig.width, merged.width);
        h = max(orig.height, merged.height);
        resizeImage(orig,w,h);
        resizeImage(merged,w,h);
    } else {
        w = min(orig.width - startX, merged.width);
        h = min(orig.height - startY, merged.height);
        cropImage(orig,{startX,startY}, {w,h});
        cropImage(merged,{0,0}, {w,h});
    }

    // create Temp image    
    Image temp(w,h);

    for(int x = 0; x < w; ++x) {
        for(int y = 0; y < h; ++y) {
            for(int c = 0; c < temp.channels; ++c) {
                float val = (1-dx) * orig(x,y,c) + dx * merged(x,y,c);
                temp(x,y,c) = min(255.0f, max(0.0f,val));
            }
        }
    }

    swap(orig,temp);
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
        swap(orig,res);
    }

}

// Amr Atif 20240398
void  TransformOperations::cropImage(Image  &orig, std::pair<int,int> st, std::pair<int,int> dimension) {
    Image temp(dimension.first, dimension.second); 
    for (int i = 0; i < dimension.first; i++) {           
        for (int j = 0; j < dimension.second; j++) {       
            for (int c = 0; c < orig.channels; c++) {
                temp(i, j, c) = orig(st.first + i, st.second + j, c);
            }
        }
    }
    swap(orig,temp);
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
                
                int x0 = min(orig.width-1,max(0,x));
                int x1 = min(orig.width-1,max(0,x+1));
                int y0 = min(orig.height-1,max(0,y));
                int y1 = min(orig.height-1,max(0,y+1));
                float top = orig(x0, y0, c) * (1 - dx) + orig(x1, y0, c) * dx;
                float bottom = orig(x0, y1, c) * (1 - dx) + orig(x1, y1, c) * dx;
                float val = top * (1 - dy) + bottom * dy;

                temp(i, j, c) = static_cast<uint8_t>(min(255.0f,max(0.0f,val)));
            }
        }
    }

    swap(orig,temp);
}

// Ali Wael 20240354
void TransformOperations::skew(Image &orig, float rad)
{
    int offset = ceil(fabs(tan(rad) * orig.height));
    int w = orig.width + abs(offset);
    int h = orig.height;

    Image temp(w, h);
    fill(temp.imageData, temp.imageData + w * h * temp.channels, 255);

    for (int y = 0; y < h; ++y) {
        float ratio = (float) y / (h - 1);
        int shift = ceil(offset * (1.0f - ratio));

        for (int x = 0; x < orig.width; ++x) {
            int nx = x + shift;
            if (nx >= 0 && nx < w) {
                for (int c = 0; c < orig.channels; ++c)
                    temp(nx, y, c) = orig(x, y, c);
            }
        }
    }

    swap(temp, orig);
}

//===========================================================================================================================

class ArtisticEffects {
private :
    ToneAndColorAdjustments apply;
public:
    // Constructor
    ArtisticEffects() = default;

    // Destructor
    ~ArtisticEffects() = default;

    void detectEdges(Image &orig, int radius, int threshold);
    void generateKernel(std::vector<float>& kernel, float sigma);
    void blurImage(Image &orig, float alpha);
    void boxBlur(Image &orig, int radius);
    void oilPainting(Image &orig, int radius, int intensityLevel);
};

// Ali Wael 20240354
void ArtisticEffects::detectEdges(Image &orig, int radius, int threshold) {
    apply.grayScale(orig);
    boxBlur(orig, radius);
    boxBlur(orig, radius + 1);
    boxBlur(orig, radius + 2);

    Image temp(orig);
    
    int w = orig.width;
    int h = orig.height;

    int g1[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int g2[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            int sum1 = 0, sum2 = 0;
            
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    float val = orig(x + dx, y + dy, 0);
                    sum1 += val * g1[dy + 1][dx + 1];
                    sum2 += val * g2[dy + 1][dx + 1];
                }
            }
            
            int out = (sum1 * sum1 + sum2 * sum2 >= threshold * threshold ? 0 : 255);
            for(int c = 0; c < orig.channels; ++c) {
                temp(x,y,c) = out;
            }
        }
    }

    swap(orig,temp);
}

// Youssef Mohamed Hassib 20240707
void ArtisticEffects::generateKernel(vf& kernel, float sigma) { // generates the kernel used to blur efficiently
    int radius = ceil(3 * sigma);
    int size = 2 * radius + 1;
    kernel.assign(size, 0.0f);

    float sum = 0;
    float PI = acos(-1.0f);

    for (int x = -radius; x <= radius; ++x) {
        float G = exp(-(x * x) / (2 * sigma * sigma)) / (2 * PI * sigma * sigma);
        kernel[x + radius] = G;
        sum += G;
    }

    for (int x = 0; x < size; ++x)
        kernel[x] /= sum;
}

// Youssef Mohamed Hassib 20240707
void ArtisticEffects::blurImage(Image &orig, float alpha) {
    if(alpha < 1e-9) return;
    vf kernel;
    generateKernel(kernel, alpha);
    int half = kernel.size() / 2;
    Image temp(orig);
    // Blurring horizontally (1D)
    for (int y = 0; y < temp.height; ++y) {
        for (int x = 0; x < temp.width; ++x) {
            for (int c = 0; c < temp.channels; ++c) {
                float val = 0;
                for (int dk = -half; dk <= half; ++dk) {
                    int x2 = max(0, min(x + dk, temp.width - 1));
                    val += orig(x2, y, c) * kernel[dk + half];
                }
                temp(x, y, c) = min(255.0f, max(val, 0.0f));
            }
        }
    }

    orig = temp;
    // Blurring vertically (1D)
    for (int y = 0; y < temp.height; ++y) {
        for (int x = 0; x < temp.width; ++x) {
            for (int c = 0; c < temp.channels; ++c) {
                float val = 0;
                for (int dk = -half; dk <= half; ++dk) {
                    int y2 = max(0, min(y + dk, temp.height - 1));
                    val += orig(x, y2, c) * kernel[dk + half];
                }

                temp(x, y, c) = min(255.0f, max(val, 0.0f));
            }
        }
    }
    swap(orig,temp);
}

void ArtisticEffects::boxBlur(Image &orig, int radius) {
    using vi = vector<int>;
    using vvi = vector<vi>;
    using vvvi = vector<vvi>;
    vvvi pre(orig.height + 1, vvi(orig.width + 1, vi(orig.channels, 0)));
    for (int i = 0; i <= orig.width; ++i) {
        for (int j = 0; j <= orig.height; ++j) {
            for (int k = 0; k < orig.channels; ++k) {
                if(i && j )pre[j][i][k] = orig(i-1, j-1, k);
                if (i)pre[j][i][k] += pre[j][i - 1][k];
                if(j)pre[j][i][k] += pre[j-1][i][k];
                if(i && j) pre[j][i][k] -= pre[j-1][i-1][k];
            }
        }
    }

    for (int i = 0; i < orig.width; ++i) {
        for (int j = 0; j < orig.height; ++j) {
            for (int k = 0; k < orig.channels; ++k) {
                int x1 = max(0, i - radius);
                int x2 = min(i + radius, orig.width - 1);
                int y1 = max(0, j - radius);
                int y2 = min(j + radius, orig.height - 1);

                int count = (y2 - y1 + 1) * (x2 - x1 + 1);
                int sum = pre[y2+1][x2+1][k] + pre[y1][x1][k] - pre[y2+1][x1][k] - pre[y1][x2+1][k];
                orig(i,j,k) = sum/count;
            }
        }
    }
}

// Ali Wael 20240354
void ArtisticEffects::oilPainting(Image &orig, int radius, int intensityLevel)
{
    using vi = vector<int>;
    using vvi = vector<vi>;

    intensityLevel = min(intensityLevel, 20);

    Image temp(orig);

    vvi intensityMap(orig.width, vi(orig.height));
    for (int x = 0; x < orig.width; ++x) {
        for (int y = 0; y < orig.height; ++y) {
            int r = orig(x,y,0), g = orig(x,y,1), b = orig(x,y,2);
            intensityMap[x][y] = ((r + g + b) * intensityLevel) / (3 * 255);
        }
    }
    
    vector<int> bin(intensityLevel + 1, 0), red(intensityLevel + 1, 0) , green(intensityLevel + 1, 0), blue(intensityLevel + 1, 0);

    for (int y = 0; y < orig.height; ++y) {
        fill(bin.begin(), bin.end(), 0);
        fill(red.begin(), red.end(), 0);
        fill(green.begin(), green.end(), 0);
        fill(blue.begin(), blue.end(), 0);
        for(int dx = 0; dx <= radius; ++dx) {
            if(dx >= orig.width) continue;
            for(int dy = -radius; dy <= radius; ++dy) {
                int ny = y + dy;
                if(ny < 0 || ny >= orig.height) continue;

                int i = intensityMap[dx][ny];
                bin[i]++;
                red[i] += orig(dx,ny,0);
                green[i] += orig(dx,ny,1);
                blue[i] += orig(dx,ny,2);
            }
        }

        for (int x = 0; x < orig.width; ++x) {
            int bestI = 0, bestCount = 0;
            for (int i = 0; i <= intensityLevel; ++i) {
                if (bin[i] > bestCount) {
                    bestCount = bin[i], bestI = i;
                }
            }
            temp(x,y,0) = red[bestI] / bestCount;
            temp(x,y,1) = green[bestI] / bestCount;
            temp(x,y,2) = blue[bestI] / bestCount;

            int x1 = x - radius;

            if(x1 >= 0) {
                for(int dy = -radius; dy <= radius; ++dy) {
                    int ny = y + dy;
                    if(ny < 0 || ny >= orig.height) continue;

                    int i = intensityMap[x1][ny];
                    bin[i]--;
                    red[i] -= orig(x1,ny,0);
                    green[i] -= orig(x1,ny,1);
                    blue[i] -= orig(x1,ny,2);
                }
            }

            int x2 = x + radius + 1;

            if(x2 < orig.width) {
                for(int dy = -radius; dy <= radius; ++dy) {
                    int ny = y + dy;
                    if(ny < 0 || ny >= orig.height) continue;

                    int i = intensityMap[x2][ny];
                    bin[i]++;
                    red[i] += orig(x2,ny,0);
                    green[i] += orig(x2,ny,1);
                    blue[i] += orig(x2,ny,2);
                }
            }
        }
    }

    swap(orig, temp);
}

//===========================================================================================================================

class Overlay{
public:
    Overlay() = default;
    ~Overlay() = default;

    void addSolidFrame(Image &orig, float thickness);
    void addBee(Image &orig, float thickness);
};

void Overlay::addSolidFrame(Image &orig, float thickness) { // add(r, g, b sliders to play with the color of the frame
    int nw = orig.width + (2 * thickness);
    int nh = orig.height + (2 * thickness);

    Image framed(nw, nh);
    for (int y = 0; y < nh; ++y) {
        for (int x = 0; x < nw; ++x) {
            framed(x, y, 0) = 0;
            framed(x, y, 1) = 255;
            framed(x, y, 2) = 0;
        }
    }

    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            for (int c = 0; c < 3; ++c) {
                framed(x + thickness, y + thickness, c) = orig(x, y, c);
            }
        }
    }
    orig = framed;
}

void Overlay::addBee(Image &orig, float thickness) {
    int nw = orig.width + (2 * thickness);
    int nh = orig.height + (2 * thickness);

    Image framed(nw, nh);
    for (int y = 0; y < nh; ++y) {
        for (int x = 0; x < nw; ++x) {
            for (int i = 0; i < framed.channels; ++i) {
                framed(x, y, i) = 0;
            }
        }
    }
    if ((int) thickness == 0) thickness += 1;

    for (int by = 0; by < nh; by += (int) thickness) {
        for (int bx = 0; bx < nw; bx += (int) thickness) {
            if (((bx / (int) thickness) + (by / (int) thickness)) % 2 == 0) {
                for (int y = by; y < by + thickness && y < nh; ++y) {
                    for (int x = bx; x < bx + thickness && x < nw; ++x) {
                        framed(x, y, 0) = 255;
                        framed(x, y, 1) = 165;
                        framed(x, y, 2) = 0;
                    }
                }
            }
        }
    }

    for (int y = thickness; y < framed.height - thickness + 1; ++y) {
        for (int x = thickness; x < framed.width - thickness + 1; ++x) {
            for (int k = 0; k < orig.channels; ++k) {
                framed(x, y, k) = orig(x - thickness, y - thickness, k);
            }
        }
    }
    orig = framed;
}

//===========================================================================================================================

class Manager {
private:
    ToneAndColorAdjustments color;
    TransformOperations transform;
    ArtisticEffects art;
    Overlay layer;
public:
    void grayScale(Image &orig);
    void blackWhite(Image &orig);
    void invertImage(Image &orig);
    void darkenLightn(Image &orig, int percent);
    void contrast(Image &orig, int percent);
    void purbleFilter(Image &orig);
    void infraredFilter(Image &orig,float percent);
    void sun(Image& orig, int percent);
    void tv(Image& orig);
    void mergeImage(Image &orig, Image &merged, int option, int transparency, int startX, int startY);
    void flipImage(Image &orig, bool& horiz);
    void rotateImage(Image &orig, int degree);
    void cropImage(Image  &orig, pair<int,int> st, pair<int,int> dimension);
    void resizeImage(Image &orig, int width, int height);
    void skew(Image &orig, float rad);
    void detectEdges(Image &orig, int radius, int threshold);
    void blurImage(Image &orig, float alpha);
    void oilPainting(Image &orig, int radius, int intensityLevel);
    void addSolidFrame(Image &orig, float thickness);
    void addBee(Image &orig, float thickness);
    void boxBlur(Image &orig, int radius);
};

void Manager::grayScale(Image &orig)
{
    color.grayScale(orig);
}

void Manager::blackWhite(Image &orig)
{
    color.blackWhite(orig);
}

void Manager::invertImage(Image &orig)
{
    color.invertImage(orig);
}

void Manager::darkenLightn(Image &orig, int percent)
{
    color.darkenLightn(orig, percent);
}

void Manager::contrast(Image &orig, int percent)
{
    color.contrast(orig, percent);
}

void Manager::purbleFilter(Image &orig)
{
    color.purbleFilter(orig);
}

void Manager::infraredFilter(Image &orig, float percent)
{
    color.infraredFilter(orig, percent);
}

void Manager::sun(Image &orig, int percent)
{
    color.sun(orig, percent);
}

void Manager::tv(Image &orig)
{
    color.tv(orig);
}

void Manager::mergeImage(Image &orig, Image &merged, int option, int transparency, int startX, int startY)
{
    transform.mergeImage(orig, merged, option, transparency, startX, startY);
}

void Manager::flipImage(Image &orig, bool &horiz)
{
    transform.flipImage(orig, horiz);
}

void Manager::rotateImage(Image &orig, int degree)
{
    transform.rotateImage(orig, degree);
}

void Manager::cropImage(Image &orig, pair<int, int> st, pair<int, int> dimension)
{
    transform.cropImage(orig, st, dimension);
}

void Manager::resizeImage(Image &orig, int width, int height)
{
    transform.resizeImage(orig, width, height);
}

void Manager::skew(Image &orig, float rad)
{
    transform.skew(orig, rad);
}

void Manager::detectEdges(Image &orig, int radius, int threshold)
{
    art.detectEdges(orig, radius, threshold);
}

void Manager::blurImage(Image &orig, float alpha)
{
    art.blurImage(orig, alpha);
}

void Manager::oilPainting(Image &orig, int radius, int intensityLevel)
{
    art.oilPainting(orig, radius, intensityLevel);
}

void Manager::addSolidFrame(Image &orig, float thickness)
{
    layer.addSolidFrame(orig, thickness);
}

void Manager::addBee(Image &orig, float thickness)
{
    layer.addBee(orig, thickness);
}

void Manager::boxBlur(Image &orig, int radius) {
    art.boxBlur(orig, radius);
}

//===========================================================================================================================

class Menu {
    private:
        Manager applyFilter;
        Image img;
        string path = "image/";
        string name = "";
        enum TYPE {
            SAVE = 1,
            LOAD,
            BACK,
            UNDO,
            REDO,
            GRAY,
            BLACK_WHITE, 
            INVERT, 
            MERGE, 
            FLIP, 
            ROTATE,
            BRIGHTNESS,
            CROP,
            DETECT_EDGES,
            RESIZE,
            BLUR,
            CONTRAST,
            PURPLE,
            INFRARED,
            SUN,
            TV,
            SOLID_FRAME,
            ALT_FRAME,
            SKEW,
            OIL_PAINTING
        };
        stack<Image> undo, redo;
        void clear();
        void pause();
        bool invalidChoice(int option, int mx, const std::string &message, int mn = 1);
        void centerize(const std::string &menuName, int width);
        void printStart();
        void printFilter();
        bool backContinue();
        void putToUndo();

    public:
        void startMenu();
        bool loadImage(Image& orig, std::string& origName);
        void filterMenu();
        void saveImage();
        void grayScale();
        void blackWhite();
        void invertImage();
        void mergeImage();
        void flipImage();
        void rotateImage();
        void brightness();
        void cropImage();
        void detectEdges();
        void resizeImage();
        void blurImage();
        void contrast();
        void purbleFilter();
        void infraredFilter();
        void xdoF(stack<Image> &st, stack<Image> &en, const string &msg);
        void sun();
        void tv();
        void addSolidFrame();
        void addBee();
        void skew();
        void oilPainting();
};

void Menu::clear() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Menu::pause() {
    system("pause");
}

bool Menu::invalidChoice(int option, int mx, const string &message, int mn) {
    if (cin.fail() || option < mn || option > mx) {
        clear();
        cerr << message << "\n";
        pause();
        cout << "\n\n";
        return true;
    }
    return false;
}

void Menu::centerize(const string &menuName, int width) {
    int spaces = max(0, (int) (width - menuName.size()) / 2);
    cout << string(spaces, ' ') << menuName << "\n";
}

void Menu::printStart() {
    cout << '\n' << string(37, '=') << '\n';
    centerize("== Start Menu ==", 37);
    cout << string(37, '=') << '\n';
    cout << left << setw(3) << 1 << " : Load Image\n";
    cout << left << setw(3) << 2 << " : Exit\n\n";
}

void Menu::printFilter() {
    cout << '\n' << string(37, '=') << '\n';
    centerize("== File Options ==", 37);
    cout << string(37, '=') << '\n';
    cout << left << setw(3) << 1 << " : Save Image\n";
    cout << left << setw(3) << 2 << " : Load new Image\n";
    cout << left << setw(3) << 3 << " : Back\n";
    cout << left << setw(3) << 4 << " : Undo\n";
    cout << left << setw(3) << 5 << " : Redo\n";
    cout << '\n' << string(37, '=') << '\n';
    centerize("== Filter ==", 37);
    cout << string(37, '=') << '\n';
    cout << left << setw(3) << 6 << " : Gray\n";
    cout << left << setw(3) << 7 << " : BW\n";
    cout << left << setw(3) << 8 << " : Invert\n";
    cout << left << setw(3) << 9 << " : Merge\n";
    cout << left << setw(3) << 10 << " : Flip\n";
    cout << left << setw(3) << 11 << " : Rotate\n";
    cout << left << setw(3) << 12 << " : Brightness\n";
    cout << left << setw(3) << 13 << " : Crop\n";
    cout << left << setw(3) << 14 << " : Detect Edges\n";
    cout << left << setw(3) << 15 << " : Resize\n";
    cout << left << setw(3) << 16 << " : Blur\n";
    cout << left << setw(3) << 17 << " : Contrast\n";
    cout << left << setw(3) << 18 << " : Purple\n";
    cout << left << setw(3) << 19 << " : Infrared\n";
    cout << left << setw(3) << 20 << " : Sun\n";
    cout << left << setw(3) << 21 << " : Tv\n";
    cout << left << setw(3) << 22 << " : Solid ColorFrame\n";
    cout << left << setw(3) << 23 << " : Alternating Colors Frame\n";
    cout << left << setw(3) << 24 << " : Skew Image\n";
    cout << left << setw(3) << 25 << " : Oil Painting\n\n";
}

bool Menu::backContinue() {
    cout << setw(3) << 1 << " : Continue\n";
    cout << setw(3) << 2 << " : Back\n\n";
    int op;
    cout << "Enter option: ";
    cin >> op;

    if (invalidChoice(op, 2, "Input must be from options", 1)) {
        return true;
    }

    if (op == 2) {
        cout << "Return successfuly\n\n";
        pause();
        return true;
    }

    return false;
}

void Menu::putToUndo() {
    undo.push(this->img);
    while (!redo.empty()) {
        redo.pop();
    }
}

void Menu::startMenu() {

    while (true) {
        printStart();
        int option;
        cout << "Choose Option: ";
        cin >> option;


        if (invalidChoice(option, 2, "Input must be from options", 1)) {
            continue;
        }

        switch (option) {
            case 1:
                if (loadImage(this->img, this->name)) {
                    pause();
                    filterMenu();
                    cout << "Returned successfully\n";
                    pause();
                    cout << "\n\n";
                } else {
                    pause();
                    cout << "\n\n";
                    continue;
                }
                break;

            case 2:
                cout << "Goodbye\n\n";
                return;
        }
    }

}

bool Menu::loadImage(Image &orig, string &origName) {

    cout << setw(3) << 1 << " : Continue\n";
    cout << setw(3) << 2 << " : Back\n\n";
    int op;
    cout << "Enter option: ";
    cin >> op;

    if (cin.fail() || op < 1 || op > 2) {
        clear();
        cerr << "Input must be from options" << "\n";
        cout << "\n\n";
        return false;
    }

    if (op == 2) {
        cout << "Return successfuly\n\n";
        return false;
    }

    cout << "Enter image name with extension: ";
    cin >> origName;

    try {
        orig.loadNewImage(path + origName);
    }
    catch (const exception &e) {
        cerr << e.what() << "\n";
        return false;
    }

    cout << "Loaded successfully\n";
    cout << "\n\n";

    return true;
}

void Menu::filterMenu() {

    while (true) {

        printFilter();

        int option;
        cout << "Enter Option: ";
        cin >> option;


        if (invalidChoice(option, 25, "Input must be from options", 1)) {
            continue;
        }

        switch (option) {
            case SAVE:
                saveImage();
                break;

            case LOAD:
                loadImage(this->img, this->name);
                pause();
                break;

            case BACK:
                return;

            case UNDO:
                xdoF(this->undo, this->redo, "No more actions to undo!\n");
                break;

            case REDO:
                xdoF(this->redo, this->undo, "No more actions to redo!\n");
                break;

            case GRAY:
                grayScale();
                break;

            case BLACK_WHITE:
                blackWhite();
                break;

            case INVERT:
                invertImage();
                break;

            case MERGE:
                mergeImage();
                break;

            case FLIP:
                flipImage();
                break;

            case ROTATE:
                rotateImage();
                break;

            case BRIGHTNESS:
                brightness();
                break;

            case CROP:
                cropImage();
                break;

            case DETECT_EDGES:
                detectEdges();
                break;

            case RESIZE:
                resizeImage();
                break;

            case BLUR:
                blurImage();
                break;

            case CONTRAST:
                contrast();
                break;

            case PURPLE:
                purbleFilter();
                break;

            case INFRARED:
                infraredFilter();
                break;
            case SUN:
                sun();
                break;
            case TV:
                tv();
                break;
            case SOLID_FRAME:
                addSolidFrame();
                break;
            case ALT_FRAME:
                addBee();
                break;
            case SKEW:
                skew();
                break;
            case OIL_PAINTING:
                oilPainting();
                break;
        }
        cout << "\n\n";
    }
}

void Menu::saveImage() {
    if (backContinue()) {
        return;
    }

    cout << setw(3) << 1 << " : Save to current image\n";
    cout << setw(3) << 2 << " : Save as new image\n\n";

    int option;
    cout << "Enter option: ";
    cin >> option;

    if (invalidChoice(option, 2, "Input must be from options", 1)) {
        return;
    }

    if (option == 1) {
        this->img.saveImage(path + name);
        cout << "SAVED SUCCESSFULLY\n";
        pause();
        return;
    }
    cout << "Enter name of the new image with extension: ";
    string newName;
    cin >> newName;

    try {
        img.saveImage(path + newName);
    }
    catch (const exception &e) {
        cerr << e.what() << "\n";
        pause();
        return;
    }

    cout << "SAVED SUCCESSFULLY\n";
    pause();
}

void Menu::grayScale() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    applyFilter.grayScale(this->img);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::blackWhite() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    applyFilter.blackWhite(this->img);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::invertImage() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    applyFilter.invertImage(this->img);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::mergeImage() {
    if (backContinue()) {
        return;
    }
    string newName;
    Image merged;
    int x = 1, y = 1;
    if (!loadImage(merged, newName)) {
        pause();
        return;
    }
    cout << setw(3) << 1 << " : Resize both to max width and height\n";
    cout << setw(3) << 2 << " : Get the common area\n\n";

    cout << "Enter Option: ";
    int option;
    cin >> option;

    if (invalidChoice(option, 2, "Input must be from options", 1)) {
        return;
    }

    int transparency;

    cout << "Enter Transparency of first image(integer between [0,100]): ";
    cin >> transparency;


    if (invalidChoice(transparency, 100, "Input must be integer between [0,100]", 1)) {
        return;
    }

    if (option == 2) {


        cout << "Enter the top-left coordinates where you want to place the new image\n";
        cout << "Enter x(integer between [1," << this->img.width << "]) : ";
        cin >> x;

        string msg1 = "x must be integer between [1," + to_string(this->img.width) + "]";
        string msg2 = "y must be integer between [1," + to_string(this->img.height) + "]";
        if (invalidChoice(x, this->img.width, msg1, 1)) {
            return;
        }
        cout << "Enter y(integer between [1," << this->img.height << "]) : ";
        cin >> y;

        if (invalidChoice(y, this->img.height, msg2, 1)) {
            return;
        }
    }

    putToUndo();
    applyFilter.mergeImage(this->img, merged, option, transparency, x - 1, y - 1);

    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::flipImage() {
    if (backContinue()) {
        return;
    }
    cout << left << setw(3) << 1 << " : Horizontal\n";
    cout << left << setw(3) << 2 << " : Vertical\n\n";
    cout << "Enter option: ";
    int option;
    cin >> option;

    if (invalidChoice(option, 2, "Input must be from options", 1)) {
        return;
    }
    bool horiz = (option == 1 ? true : false);
    putToUndo();
    applyFilter.flipImage(this->img, horiz);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::rotateImage() {
    if (backContinue()) {
        return;
    }
    cout << "Enter degree (must be divisible by 90): ";
    int degree;
    cin >> degree;
    if (invalidChoice(degree, INT_MAX, "Input must be integer", INT_MIN)) {
        return;
    }
    int n = (-degree + 359) / 360;
    if (degree < 0) degree += n * 360;

    if (degree % 90 != 0) {
        cerr << "Input must be divisible by 90\n\n\n";
        pause();
        return;
    }
    putToUndo();
    applyFilter.rotateImage(this->img, degree);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::brightness() {
    if (backContinue()) {
        return;
    }
    cout << "Enter percentage[-100,100]: ";
    int option;
    cin >> option;

    if (invalidChoice(option, 100, "Input must be integer from range [-100,100]", -100)) {
        return;
    }
    putToUndo();
    applyFilter.darkenLightn(this->img, option);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::cropImage() {
    if (backContinue()) {
        return;
    }
    cout << "Enter the top left point\n";
    cout << "Enter x: ";
    int x, y;
    cin >> x;

    string msg1 = "x must be integer between [1," + to_string(this->img.width) + "]";
    string msg2 = "y must be integer between [1," + to_string(this->img.height) + "]";
    if (invalidChoice(x, this->img.width, msg1, 1)) {
        return;
    }
    cout << "Enter y: ";
    cin >> y;

    if (invalidChoice(y, this->img.height, msg2, 1)) {
        return;
    }
    int width, height;
    cout << "Enter width: ";
    cin >> width;

    if (invalidChoice(width, this->img.width - x + 1, "Invalid width", 1)) {
        return;
    }
    cout << "Enter height: ";
    cin >> height;

    if (invalidChoice(height, this->img.height - y + 1, "Invalid width", 1)) {
        return;
    }

    putToUndo();
    applyFilter.cropImage(this->img, {x - 1, y - 1}, {width, height});
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::detectEdges() {
    if (backContinue()) {
        return;
    }
    int percent;
    cout << "Enter Edge sharpness[0,100]: ";
    cin >> percent;
    if (invalidChoice(percent, 100, "Input must be integer from range [0,100]", 0)) {
        return;
    }
    int threshhold = 120 - 0.9 * percent;

    putToUndo();
    applyFilter.detectEdges(this->img, 2, threshhold);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::resizeImage() {
    if (backContinue()) {
        return;
    }
    cout << "Enter new width: ";
    int width;
    cin >> width;

    if (invalidChoice(width, INT_MAX, "Invalid width", 1)) {
        return;
    }
    cout << "Enter new height: ";
    int height;
    cin >> height;

    if (invalidChoice(height, INT_MAX, "Invalid height", 1)) {
        return;
    }

    putToUndo();
    applyFilter.resizeImage(this->img, width, height);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::blurImage() {
     if (backContinue()) {
        return;
    }
    cout << setw(3) << 1 << " : Faster Blur\n";
    cout << setw(3) << 2 << " : Quality Blur(Gaussian Blur)\n";
    cout << "Pick the preferred blur type from [1,2]: ";


    int op;
    cin >> op;
    if (invalidChoice(op, 2, "Input must be an integer from range [1,2]", 1)) {
        return;
    }
    if (op == 1) {
        int radius;
        cout << "Enter radius: ";
        cin >> radius;

        if (invalidChoice(op, 100, "Input must be an integer from range [1,100]", 1)) {
            return;
        }
        putToUndo();
        applyFilter.boxBlur(this->img, radius);
        applyFilter.boxBlur(this->img, radius+1);
        applyFilter.boxBlur(this->img, radius+2);
        cout << "DONE SUCCESSFULLY\n";
        pause();
    } else {
        cout << "Enter percentage of blur from [0,100] : ";
        int percent;
        cin >> percent;

        if (invalidChoice(percent, 100, "Input must be integer from range [0,100]", 0)) {
            return;
        }
        float sigma = (15.0f * percent) / 100.0f;

        putToUndo();
        applyFilter.blurImage(this->img, sigma);
        cout << "DONE SUCCESSFULLY\n";
        pause();
    }
}

void Menu::contrast() {
    if (backContinue()) {
        return;
    }
    cout << "Enter percentage[-100,100]: ";
    int option;
    cin >> option;

    if (invalidChoice(option, 100, "Input must be integer from range [-100,100]", -100)) {
        return;
    }

    putToUndo();
    applyFilter.contrast(this->img, option);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::xdoF(stack<Image> &st, stack<Image> &en, const string &msg) {
    if (st.empty()) {
        cout << msg << '\n';
        pause();
        return;
    }
    en.push(this->img);
    this->img = st.top();
    st.pop();
    cout << "DONE SUCCESSFULLY\n";
}

void Menu::purbleFilter() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    applyFilter.purbleFilter(this->img);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::infraredFilter() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    cout << "Enter percentage: ";
    int op;
    cin >> op;
    if (invalidChoice(op, 100, "Enter integer between 0 to 100", 0)) {
        return;
    }
    applyFilter.infraredFilter(this->img, op / 100.0f);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::sun() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    cout << "Enter percentage: ";
    int op;
    cin >> op;
    if (invalidChoice(op, 100, "Enter integer between 0 to 100", 0)) {
        return;
    }
    applyFilter.sun(this->img, op / 100.0f);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::tv() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    applyFilter.tv(this->img);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}


void Menu::addSolidFrame() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    cout << "Enter percentage: ";
    int op;
    cin >> op;
    if (invalidChoice(op, 100, "Enter integer between 0 to 100", 0)) {
        return;
    }
    op = 100 - op;
    applyFilter.addSolidFrame(this->img, min(img.height, img.width) / op);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::addBee() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    cout << "Enter percentage: ";
    int op;
    cin >> op;
    if (invalidChoice(op, 100, "Enter integer between 0 to 100", 0)) {
        return;
    }
    op = 100 - op;
    applyFilter.addBee(this->img, min(img.height, img.width) / max(1,op));
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::skew() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    cout << "Enter Degree [0,89]: ";
    int op;
    cin >> op;
    if (invalidChoice(op, 89, "Enter integer between 0 to 89", 0)) {
        return;
    }
    applyFilter.skew(this->img, acos(-1) / 180 * op);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::oilPainting() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    cout << "Enter percentage [0,100]: ";
    int op;
    cin >> op;
    if (invalidChoice(op, 100, "Enter integer between 0 to 100", 0)) {
        return;
    }
    op = max(1, op/10);
    if(op != 0) applyFilter.oilPainting(this->img, op, 20);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

int main()
{
    cout << string(45,'=') << '\n';
    string menuName = "== Welcom to Baby Photoshop ==";
    int spaces = max(0,(int)(45 - menuName.size()) / 2);
    cout << string(spaces, ' ') << menuName << "\n";
    cout << string(45,'=') << "\n\n\n\n";
    Menu run;
    run.startMenu();
    return 0;
}
