/**
 * @File  :
 * @brief :
 *
 * @authors :
 *
 * @copyright : 
 * @version   :
 * @date      :
 */

#pragma once

#include "Model.h"

#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdint>

/**
 * @class
 * @brief
 */

class Filter : public Model {
public:
    // Constructor
    Filter() = default;

    // Destructor
    ~Filter() = default;

    void grayScale(Image &orig) override; // Grayscale Conversion
    void blackWhite(Image &orig) override; // Black and White
    void invertImage(Image &orig) override; // Invert Images
    void mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int startX, int startY) override; // Merge Images
    void flipImage(Image &orig, bool& horiz) override; // Flip Image
    void rotateImage(Image &orig, int degree) override; // Rotate Image
    void darkenLightn(Image &orig, int percent) override; // Darken and Lighten Image
    void cropImage(Image  &orig, std::pair<int,int> st, std::pair<int,int> dimension) override;// Crop Image
    void addFrame(Image &orig, Image* frame) override; // Adding a Frame to the Picture
    void detectEdges(Image &orig, float alpha, int tresh) override; // Detect Image Edges
    void resizeImage(Image &orig, int width, int height) override; // Resize Image
    void generateKernel(std::vector<float>& kernel, float sigma);
    void blurImage(Image &orig, float alpha) override; // Blur Image
    void contrast(Image &orig, int percent) override; // Adjust Contrast
    void oilPainting(Image &orig, int radius, int intensityLevel) override; // Image -> Oil Painting
    void skew(Image &orig, float rad) override; // Image -> Oil Painting
};