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

}

void Filter::blackWhite(Image &orig) {

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

void Filter::mergeImage(Image &orig1, Image &orig2, int option, int transparency) {

}

void Filter::flipImage(Image &orig, int option) {

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

void Filter::darkenLightn(Image &orig, int percent) {

}

void Filter::cropImage(Image &orig, std::pair<int, int> st, std::pair<int, int> end) {

}

void Filter::addFrame(Image &orig, Image &frame) {

}

void Filter::detectEdges(Image &orig) {

}

void Filter::resizeImage(Image &orig, int width, int height) {

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


// ########################################################Testing Area##################################################################
void test() {
    Image img("mario.jpg");

    Filter f;
    //f.invertImage(img);
    //f.rotateImage(img, 180);
    //f.grayScale(img);
    //f.blackWhite(img);
    //f.resizeImage(img, 2000, 1800);
    //f.mergeImage(img, img1, 2, 30);
    //f.blurImage(img, 20, 5);
    //f.rotateImage(img, 180);
    // f.cropImage(img, {1, 1}, {2000, 1800});
    f.rotateImage(img, 180);
    img.saveImage("luffy25.jpg");
    cout << "Finished Successfully!!\n";
}

int main() {
    test();
    return 0;
}
