#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "header/Winged_Dragon/Filter.h"
#include <iostream>

using namespace std;

void Filter::grayScale(Image &orig) {
    Image res(orig.width, orig.height);
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
    for (int i = 0; i < orig.width; ++i) {
        for (int j = 0; j < orig.height; ++j) {
            orig(i, j, 0) = 255 - orig(i, j, 0);
            orig(i, j, 1) = 255 - orig(i, j, 1);
            orig(i, j, 2) = 255 - orig(i, j, 2);
        }
    }

}

void Filter::mergeImage(Image &orig, int option, int transpaerncy) {

}

void Filter::flipImage(Image &orig, int option) {

}


void Filter::rotateImage(Image &orig, int degree) {
    int n = degree / 90; // dependent on degree % 90 == 0
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

void Filter::addFrame(Image &orig, Image *frame) {

}

void Filter::detectEdges(Image &orig) {

}

void Filter::resizeImage(Image &orig, int width, int height) {

}

inline int check(int cur, int low, int high) {
    return (cur < low) ? low : (cur > high ? high : cur);
}

// needs fixing
void Filter::blurImage(Image &orig, int radius) {
    Image res(orig.width, orig.height);
    // kernel size is dependent on radius:
    // size = 2* radius + 1;

    double kernel[3][3] = {2, 4, 2, 4, 8, 4,
                           2, 4, 2};
    int ksum = 32;
    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            int sum[3] = {0, 0, 0};

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int nx = check(x + dx, 0, orig.width - 1);
                    int ny = check(y + dy, 0, orig.height - 1);


                    int weight = kernel[dx + 1][dy + 1];
                    for (int i = 0; i < 3; ++i) {
                        sum[i] += weight * orig.getPixel(nx, ny, i);
                    }
                }
            }

            for (int i = 0; i < 3; ++i) {
                res.setPixel(x, y, i, sum[i] / ksum);
            }
        }
    }

    orig = res;
}


// ########################################################Testing Area##################################################################
void test() {
    Image img("colorfulparrot.jpg");
    Filter f;
    //f.invertImage(img);
    //f.rotateImage(img, 180);
    //f.grayScale(img);
    //f.blackWhite(img);
    /*int n = 100;
    while(n--){
        f.blurImage(img, 19000);
    } */

    img.saveImage("luffy25.jpg");
    cout << "Finished Successfully!!\n";
}

int main() {
    test();
    return 0;
}
