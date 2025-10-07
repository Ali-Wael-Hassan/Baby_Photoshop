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

class Overlay{
public:
    Overlay() = default;
    ~Overlay() = default;

    void addSolidFrame(Image &orig, double thickness);
    void addBee(Image &orig, double thickness);
};