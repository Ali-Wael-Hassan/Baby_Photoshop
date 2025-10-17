#ifndef TRANSFORMOPERATIONS_H
#define TRANSFORMOPERATIONS_H

#include "image_class.h"
#include <algorithm>
#include <cmath>

class TransformOperations{
public:
    TransformOperations() = default;
    ~TransformOperations() = default;

    void mergeImage(Image &orig, Image &merged, int option, int transparency, int x1, int y1, int x2, int y2, int w, int h);
    void flipImage(Image &orig, bool& horiz);
    void rotateImage(Image &orig, int degree);
    void cropImage(Image  &orig, std::pair<int,int> st, std::pair<int,int> dimension);
    void resizeImage(Image &orig, int width, int height);
    void skew(Image &orig, float rad);
};

#endif // TRANSFORMOPERATIONS_H
