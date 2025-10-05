#include "Winged_Dragon/Filter.h"
#include "Filter.h"

using namespace std;

#define vf vector<float>
#define vvf vector<vector<float>>

/*
    Project : Baby Photoshop
    File    : main.cpp
    Section : S

    Team Members:
    - Ali Wael       (ID 20240354)  -> Gray Scale (1), Merge Image (4), Darken & Lighten (7), Detect Edges (10)
    - Amr Atif       (ID 20240398)  -> Black & White (2), Flip Image (5), Crop Image (8), Resize Image (11)
    - Yousef Hassib  (ID 20240707)  -> Invert Colors (3), Rotate Image (6), Blur Image (12)

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
    Second Note: put only name of the image + extension
*/

/*
    Ali-Wael 20240354
    Gray Scale use luminance formula that makes it weighted from sudies of eye's percpectoin
    0.299 for Red
    0.587 for Green
    0.114 for Blue
*/ 
// Ali Wael 20240354
void Filter::grayScale(Image &orig) {
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

// Youssef Mohamed Hassib 20240707
void Filter::invertImage(Image &orig) {
    for (int i = 0; i < orig.width; ++i) {
        for (int j = 0; j < orig.height; ++j) {
            orig(i, j, 0) = 255 - orig(i, j, 0);
            orig(i, j, 1) = 255 - orig(i, j, 1);
            orig(i, j, 2) = 255 - orig(i, j, 2);
        }
    }
}

// Ali Wael 20240354
void Filter::mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int startX, int startY) {
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


//Youssef Mohamed Hassib 20240707
void Filter::rotateImage(Image &orig, int degree) {
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

//Ali-Wael 20240354
void Filter::darkenLightn(Image &orig, int percent) {
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

// Amr Atif 20240398
void  Filter::cropImage(Image  &orig, std::pair<int,int> st, std::pair<int,int> dimension) {
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

void Filter::addFrame(Image &orig, Image *frame)
{
}
// Ali Wael 20240354
void Filter::detectEdges(Image &orig, float alpha, int tresh) {
    grayScale(orig);
    blurImage(orig, alpha);

    int w = orig.width;
    int h = orig.height;

    int g1[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int g2[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    float *arr = new float[w*h], mx = 0.0f;

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            float sum1 = 0, sum2 = 0;
            
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    float val = orig(x + dx, y + dy, 0);
                    sum1 += val * g1[dy + 1][dx + 1];
                    sum2 += val * g2[dy + 1][dx + 1];
                }
            }
            
            float grad = sqrt(sum1 * sum1 + sum2 * sum2);

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

// Amr Atif 20240398
void Filter::resizeImage(Image &orig, int width, int height) {
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

// Youssef Mohamed Hassib 20240707
void Filter::generateKernel(vf& kernel, float sigma) { // generates the kernel used to blur efficiently
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
void Filter::blurImage(Image &orig, float alpha) {
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

// Ali-Wael 20240354
void Filter::contrast(Image &orig, int percent){ 
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
// Ali Wael 20240354
void Filter::oilPainting(Image &orig, int radius, int intensityLevel)
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

    for (int x = 0; x < orig.width; ++x) {

        int *bin = new int[intensityLevel + 2]{};
        int *red = new int[intensityLevel + 2]{};
        int *green = new int[intensityLevel + 2]{};
        int *blue = new int[intensityLevel + 2]{};

        for (int y = 0; y < orig.height; ++y) {
            fill(bin, bin + intensityLevel + 2, 0);
            fill(red, red + intensityLevel + 2, 0);
            fill(green, green + intensityLevel + 2, 0);
            fill(blue, blue + intensityLevel + 2, 0);
            int bestI = 0, bestCount = 0;
            for (int dx = -radius; dx <= radius; ++dx)
                for (int dy = -radius; dy <= radius; ++dy) {
                    int nx = x + dx, ny = y + dy;
                    if (nx < 0 || nx >= orig.width || ny < 0 || ny >= orig.height) continue;

                    int i = intensityMap[nx][ny];
                    bin[i]++;
                    red[i] += orig(nx,ny,0);
                    green[i] += orig(nx,ny,1);
                    blue[i] += orig(nx,ny,2);

                    if (bin[i] > bestCount) {
                        bestCount = bin[i];
                        bestI = i;
                    }
                }

            temp(x,y,0) = red[bestI] / bestCount;
            temp(x,y,1) = green[bestI] / bestCount;
            temp(x,y,2) = blue[bestI] / bestCount;
        }
        delete [] bin;
        delete [] red;
        delete [] green;
        delete [] blue;
    }

    swap(orig, temp);
}
// Ali Wael 20240354
void Filter::skew(Image &orig, float rad)
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