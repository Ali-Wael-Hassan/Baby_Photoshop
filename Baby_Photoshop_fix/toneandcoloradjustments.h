#pragma once
#include <algorithm>
#include <cmath>
#include "Image_Class.h"
#include <cstdlib>
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
    void infraredFilter(Image &orig);
    void sun(Image& orig, int percent);
    void tv(Image& orig);
    void oldPhoto(Image &orig);
};
