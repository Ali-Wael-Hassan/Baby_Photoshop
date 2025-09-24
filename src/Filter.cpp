#include "Winged_Dragon/Filter.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>


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
    Image res(orig.width, orig.height);
    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            int r = orig(x, y, 0);
            int g = orig(x, y, 1);
            int b = orig(x, y, 2);

            int gray = 0.299 * r + 0.587 * g + 0.114 * b;

            if (gray >= (255) / 2) gray = 255;
            else gray = 0;
            orig(x, y, 0) = orig(x, y, 1) =
            orig(x, y, 2) = gray;
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

void Filter::flipImage(Image &orig, bool& horiz) {
    
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
                else orig(x,y,c) = std::min(255.0,(1+v) * orig(x,y,c));
            }
        }
    }
}

void Filter::cropImage(Image &orig, std::pair<int,int> st, std::pair<int,int> dimention) {
    
}



void Filter::addFrame(Image &orig, Image *frame) {

}

void Filter::detectEdges(Image &orig, double alpha, int tresh) {
    grayScale(orig);
    if(alpha > 0.0) blurImage(orig, alpha,1);

    int w = orig.width;
    int h = orig.height;

    int g1[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int g2[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

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

void Filter::resizeImage(Image &orig, int width, int height) {

}

void generateKernel(std::vector<std::vector<double>>& kernel, int size, double sigma = 2) {
    // size always odd
    int half = size / 2;
    kernel.assign(size, std::vector<double>(size, 0.0));
    double PI = std::acos(-1.0);

    double sum = 0;
    for(int y = -half; y <= half; ++y) {
        for(int x = -half; x <= half; ++x) {
            double G = std::exp(-(x*x+y*y)/(2*sigma*sigma)) / (2*PI*sigma*sigma); // G(x,y) = e^{-(x^2 + y^2)/(2* sigma^2)} * 1/(2*PI*sigma^2)
            sum += (kernel[y + half][x + half] = G);
        }
    }

    for(int y = -half; y <= half; ++y) {
        for(int x = -half; x <= half; ++x) {
            kernel[y + half][x + half] /= sum;
        }
    }
}

void Filter::blurImage(Image &orig, double alpha, int size) {
    std::vector<std::vector<double>> kernel;
    generateKernel(kernel,2*size+1,alpha);
    
    int half = (2*size+1)/2;
    Image temp(orig);

    for(int y = 0; y < temp.height; ++y) {
        for(int x = 0; x < temp.width; ++x) {
            for(int c = 0; c < temp.channels; ++ c) {
                double val = 0;
                // calculate the values depends on values
                for(int dy = -half; dy <= half; ++dy) {
                    for(int dx = -half; dx <= half; ++dx) {
                        int y2 = std::max(0, std::min(y + dy, temp.height - 1));
                        int x2 = std::max(0, std::min(x + dx, temp.width - 1));
                        val += orig(x2,y2,c) *  kernel[dy+half][dx + half]; // value * contribution
                    }
                }

                temp(x,y,c) = std::min(255.0, std::max(val,0.0));
            }
        }
    }

    orig = temp;
}

void Filter::contrast(Image &orig, int percent){
    // percent -100 to 100
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
