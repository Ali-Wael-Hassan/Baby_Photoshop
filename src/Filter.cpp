#include "Winged_Dragon/Filter.h"

using namespace std;

#define vd vector<double>
#define vvd vector<vector<double>>

/*
    Project : Baby Photoshop
    File    : main.cpp
    Section : S

    Team Members:
    - Ali Wael       (ID 20240354)  -> Gray Scale (1), Merge Image (4), Darken & Lighten (7), Detect Edges (10)
    - Amr Atif       (ID 2024xxxx)  -> Black & White (2), Flip Image (5), Crop Image (8), Resize Image (11)
    - Yousef Hassib  (ID 2024yyyy)  -> Invert Colors (3), Rotate Image (6), Add Frame (9), Blur Image (12)

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
    Ali-Wael
    Gray Scale use luminance formula that makes it weighted from sudies of eye's percpectoin
    0.299 for Red
    0.587 for Green
    0.114 for Blue
*/ 
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
/*
    Ali-Wael
    Merging two images with contribution (for slide bar)
    to Merge two images the two must have the same size so we have two options:
    1) resize them to max width and max height
    2) take the min width and min height
    to make the ability to drag we use start x, start y so that we can put the second image to make different overlapping area

    Note: the drag makes start x, start y in the dimensions of first image (orig)
*/ 
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


//Youssef Mohamed Hassib 20240707
void Filter::rotateImage(Image &orig, int degree) {
    int n = degree / 90; // dependent on degree % 90 == 0, further updates to come to make it valid all 360 degrees
    while (n--) {
        Image res(orig.height, orig.width);
        for (int y = 0; y < orig.height; ++y) {
            for (int x = 0; x < orig.width; ++x) {
                for (int c = 0; c < 3; ++c) {
                    res(orig.height - 1 - y, x, c) = orig(x, y, c);
                }
            }
        }
        orig = res;
    }

}
/*
    Ali-Wael
    Adjusting brightness of an image

    Input: percent in range [-100, 100]
      1) -ve → Darken
      2) +ve → Lighten

    - We compute a factor based on abs(percent) / 100.
    - the factor is raised to the power of 1.5 to make the adjustment smoother (not just linear), 

    - +ve (lighten):
        multiplier = 1 + factor
        Example: factor = 0.5 → multiplier = 1.5 → pixel = 1.5 * pixel
    - If -ve (darken):
        multiplier = 1 - factor
        Example: factor = 0.3 → multiplier = 0.7 → pixel = 0.7 * pixel
*/
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
/*
    Ali-Wael
    Detect Edges of an Image

    Algorithm: Sobel Operator

    Steps:
    1) Convert the image to grayscale to simplify edge detection 
    2) Apply a Gaussian blur (alpha/sigma parameter) to reduce noise.

    Sobel Kernels:
    For horizontal edges (changes left - right):
          {-1, 0, 1}
    Gx =  {-2, 0, 2}
          {-1, 0, 1}

    For vertical edges (changes top - bottom):
          {-1, -2, -1}
    Gy =  { 0,  0,  0}
          { 1,  2,  1}

    Gradient is the best to represent the edge since it is horizontal and vertical
    by pythagoras
    grad = sqrt(horizontal_edge^2 + vertical_edge^2)


    Use a user-defined threshold to decide if a pixel is an edge.
    If value >= threshold  mark as edge.

    Optional:
    Invert colors so edges appear white on black background.

    Parameters:
    alpha (sigma): blur factor to smooth the image.
    threshold: minimum gradient magnitude to consider a pixel an edge.
*/
void Filter::detectEdges(Image &orig, double alpha, int tresh) { // Ali-Wael
    grayScale(orig);
    if(alpha > 1e-9) blurImage(orig, alpha,1);

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

// Youssef Mohamed Hassib 20240707
void generateKernel(vd &kernel, double sigma) { // generates the kernel used to blur efficiently
    int radius = ceil(3 * sigma);
    int size = 2 * radius + 1;
    kernel.assign(size, 0.0);

    double sum = 0;
    double PI = acos(-1.0);

    for (int x = -radius; x <= radius; ++x) {
        double G = exp(-(x * x) / (2 * sigma * sigma)) / (2 * PI * sigma * sigma);
        kernel[x + radius] = G;
        sum += G;
    }

    for (int x = 0; x < size; ++x)
        kernel[x] /= sum;
}
// Youssef Mohamed Hassib 20240707
void Filter::blurImage(Image &orig, double alpha, int size) {
    vd kernel;
    generateKernel(kernel, alpha);
    int half = kernel.size() / 2;
    Image temp(orig);
    // Blurring horizontally (1D)
    for (int y = 0; y < temp.height; ++y) {
        for (int x = 0; x < temp.width; ++x) {
            for (int c = 0; c < temp.channels; ++c) {
                double val = 0;
                for (int dk = -half; dk <= half; ++dk) {
                    int x2 = max(0, min(x + dk, temp.width - 1));
                    val += orig(x2, y, c) * kernel[dk + half];
                }
                temp(x, y, c) = min(255.0, max(val, 0.0));
            }
        }
    }

    orig = temp;
    // Blurring vertically (1D)
    for (int y = 0; y < temp.height; ++y) {
        for (int x = 0; x < temp.width; ++x) {
            for (int c = 0; c < temp.channels; ++c) {
                double val = 0;
                for (int dk = -half; dk <= half; ++dk) {
                    int y2 = max(0, std::min(y + dk, temp.height - 1));
                    val += orig(x, y2, c) * kernel[dk + half];
                }

                temp(x, y, c) = min(255.0, max(val, 0.0));
            }
        }
    }
    orig = temp;
}
/*
    Ali-Wael
    Adjusting contrast of an image

    Input: percent in range [-100, 100]
      1) -ve → reduce contrast
      2) +ve → increase contrast

    - We compute a factor based on abs(percent) / 100.

    multiplier = 1 + factor
    Example: factor = 0.5 → multiplier = 1.5 → pixel = 1.5 * pixel

    we iterate over pixels and if it is dark (x < 128) then it will be -ve so gets darker
    else gets lighter 

    Note: all of that based on the factor and the factor is /200 in dark to make -100 not fully gray
*/
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
