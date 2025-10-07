#pragma once

#include "Image_Class/Image_Class.h"
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