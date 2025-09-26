#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "header/Winged_Dragon/Filter.h"
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>

#define vd vector<double>
#define vvd vector<vector<double>>


using namespace std;

void Filter::grayScale(Image &orig) {
    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            int r = orig(x, y, 0);
            int g = orig(x, y, 1);
            int b = orig(x, y, 2);

            int gray = 0.299 * r + 0.587 * g + 0.114 * b;

            orig(x, y, 0) = orig(x, y, 1) =
            orig(x, y, 2) = gray;
        }
    }

}

void Filter::blackWhite(Image &orig) {
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
    for (int i = 0; i < orig.width; ++i) {
        for (int j = 0; j < orig.height; ++j) {
            orig(i, j, 0) = 255 - orig(i, j, 0);
            orig(i, j, 1) = 255 - orig(i, j, 1);
            orig(i, j, 2) = 255 - orig(i, j, 2);
        }
    }

}

void Filter::mergeImage(Image &orig, int option, int transparency) {

}

void Filter::flipImage(Image &orig, int option) {
    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            if (option == 1 && y >= orig.height / 2) continue; //  horizontal flips
            if (option != 1 && x >= orig.width / 2) continue; // vertical flips

            int nx = x, ny = y;
            if (option == 1) {
                ny = orig.height - 1 - y;
            } else {
                nx = orig.width - 1 - x;
            }

            for (int c = 0; c < 3; ++c) {
                swap(orig(x, y, c), orig(nx, ny, c));
            }
        }
    }
}


void Filter::rotateImage(Image &orig, int degree) {

    int n = degree / 90; // dependent on degree % 90 == 0
    while (n--) {
        Image res(orig);
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

void Filter::darkenLightn(Image &orig, int percent) {

}

void Filter::cropImage(Image &orig, std::pair<int, int> st, std::pair<int, int> end) {
    Image tmp(end.first, end.second);
    for (int i = st.first; i <= end.first; ++i) {
        for (int j = st.second; j <= end.second; ++j) {
            for (int k = 0; k < 3; ++k) {
                tmp(i, j, k) = orig(i, j, k);
            }
        }
    }
    orig = tmp;
}

void Filter::addFrame(Image &orig, Image *frame) {

}

void Filter::detectEdges(Image &orig) {

}

void Filter::resizeImage(Image &orig, int width, int height) {

}

void generateKernel(vd& kernel, double sigma) {
    int radius = ceil(3 * sigma);
    int size = 2*radius + 1;
    kernel.assign(size, 0.0);

    double sum = 0;
    double PI = acos(-1.0);

    for(int x=-radius; x<=radius; ++x) {
        double G = exp(-(x*x)/(2*sigma*sigma)) / (2*PI*sigma*sigma);
        kernel[x+radius] = G;
        sum += G;
    }

    for(int x=0; x<size; ++x)
        kernel[x] /= sum;
}

void Filter::blurImage(Image &orig, double alpha, int size) {
    vd kernel;
    generateKernel(kernel,alpha);
    int half = kernel.size()/2;
    Image temp(orig);

    for(int y = 0; y < temp.height; ++y) {
        for(int x = 0; x < temp.width; ++x) {
            for(int c = 0; c < temp.channels; ++ c) {
                double val = 0;
                for(int dk = -half; dk <= half; ++dk) {
                    int x2 = std::max(0, min(x + dk, temp.width - 1));
                    val += orig(x2,y,c) *  kernel[dk + half];
                }

                temp(x,y,c) = min(255.0, std::max(val,0.0));
            }
        }
    }

    orig = temp;

    for(int y = 0; y < temp.height; ++y) {
        for(int x = 0; x < temp.width; ++x) {
            for(int c = 0; c < temp.channels; ++ c) {
                double val = 0;
                for(int dk = -half; dk <= half; ++dk) {
                    int y2 = std::max(0, std::min(y + dk, temp.height - 1));
                    val += orig(x,y2,c) *  kernel[dk + half];
                }

                temp(x,y,c) = std::min(255.0, std::max(val,0.0));
            }
        }
    }

    orig = temp;
}


// ########################################################Testing Area##################################################################
void test() {
    Image img("building.jpg");
    Filter f;
    //f.invertImage(img);
    //f.rotateImage(img, 180);
    //f.grayScale(img);
    //f.blackWhite(img);
    /*int n = 100;
    while(n--){
        f.blurImage(img, 19000);
    } */

    f.blurImage(img, 20, 5);
    //f.rotateImage(img, 180);
    // f.cropImage(img, {1, 1}, {2000, 1800});
    img.saveImage("luffy25.jpg");
    cout << "Finished Successfully!!\n";
}

int main() {
    test();
    return 0;
}
