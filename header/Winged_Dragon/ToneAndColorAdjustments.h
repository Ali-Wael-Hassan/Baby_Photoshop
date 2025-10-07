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