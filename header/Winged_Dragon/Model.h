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

#include "Image_Class.h"

/**
 * @class
 * @brief
 */

class Model {
public:
    ~Model() = default; // for linking
    virtual void grayScale(Image &orig) = 0; // Grayscale Conversion
    virtual void blackWhite(Image &orig) = 0; // Black and White
    virtual void invertImage(Image &orig) = 0; // Invert Images
    virtual void mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int startX, int startY) = 0; // Merge Images
    virtual void flipImage(Image &orig, int option) = 0; // Flip Image
    virtual void rotateImage(Image &orig, int degree) = 0; // Rotate Image
    virtual void darkenLightn(Image &orig, int percent) = 0; // Darken and Lighten Image
    virtual void cropImage(Image &orig, std::pair<int,int> st, std::pair<int,int> end) = 0; // Crop Image
    virtual void addFrame(Image &orig, Image* frame) = 0; // Adding a Frame to the Picture
    virtual void detectEdges(Image &orig) = 0; // Detect Image Edges
    virtual void resizeImage(Image &orig, int width, int height) = 0; // resize image
    virtual void blurImage(Image &orig, int radious) = 0; // Blur Image
};