#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "header/Winged_Dragon/Filter.h"
#include <iostream>

using namespace std;

void Filter::grayScale(Image &orig) {

}

void Filter::blackWhite(Image &orig) {

}

void Filter::invertImage(Image &orig) {
    for (int i = 0; i < orig.width; ++i) {
        for (int j = 0; j < orig.height; ++j) {
            unsigned int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += orig(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            unsigned int nr = orig(i, j, 0);
            unsigned int ng = orig(i, j, 1);
            unsigned int nb = orig(i, j, 2);

            nr = 255 - nr;
            ng = 255 - ng;
            nb = 255 - nb;

            orig(i, j, 0) = nr;
            orig(i, j, 1) = ng;
            orig(i, j, 2) = nb;
        }
    }

}

void Filter::mergeImage(Image &orig, int option, int transpaerncy) {

}

void Filter::flipImage(Image &orig, int option) {

}

void Filter::rotateImage(Image &orig, int degree) {
    if (degree == 90) {
        Image res(orig.height, orig.width);
        for (int y = 0; y < res.height; ++y) {
            for (int x = 0; x < res.width; ++x) {
                for (int c = 0; c < 3; ++c) {
                    res.imageData[(y * res.width + x) * 3 + c] =
                            orig.imageData[((orig.height - 1 - x) * orig.width + y) * 3 + c];
                }
            }
        }
        orig = res;
    } else if (degree == 180) {
        Image res(orig.width, orig.height);
        for (int x = 0; x < res.height; ++x) {
            for (int y = 0; y < res.width; ++y) {
                for (int c = 0; c < 3; ++c) {
                    res.imageData[(y * res.width + x) * 3 + c] =
                            orig.imageData[((orig.height - 1 - y) * orig.width + (orig.width - x - 1)) * 3 + c];
                }
            }
        }
        orig = res;
    } else if (degree == 270) {
        Image res(orig.height, orig.width);
        for (int y = 0; y < res.height; ++y) {
            for (int x = 0; x < res.width; ++x) {
                for (int c = 0; c < 3; ++c) {
                    res.imageData[(y * res.width + x) * 3 + c] =
                            orig.imageData[(x * orig.width + (orig.width - 1 - y)) * 3 + c];
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

void Filter::addFrame(Image &orig, Image *frame) {

}

void Filter::detectEdges(Image &orig) {

}

void Filter::resizeImage(Image &orig, int width, int height) {

}

void Filter::blurImage(Image &orig, int radious) {

}


// ########################################################Testing Area##################################################################
void test() {
    Image img("luffy.jpg");
    Filter f;
    //f.invertImage(img);
    f.rotateImage(img, 270);
    img.saveImage("luffy23.jpg");
    cout << "Finished Successfully!!\n";
}

int main() {
    test();
    return 0;
}
