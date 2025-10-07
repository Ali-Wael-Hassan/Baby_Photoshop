#pragma once

#include "ArtisticEffects.h"
#include "Overlay.h"
#include "ToneAndColorAdjustments.h"
#include "TransformOperations.h"

class Manager {
private:
    ToneAndColorAdjustments color;
    TransformOperations transform;
    ArtisticEffects art;
    Overlay layer;
public:
    void grayScale(Image &orig);
    void blackWhite(Image &orig);
    void invertImage(Image &orig);
    void darkenLightn(Image &orig, int percent);
    void contrast(Image &orig, int percent);
    void purbleFilter(Image &orig);
    void infraredFilter(Image &orig,float percent);
    void sun(Image& orig, int percent);
    void tv(Image& orig);
    void mergeImage(Image &orig, Image &merged, int option, int transparency, int startX, int startY);
    void flipImage(Image &orig, bool& horiz);
    void rotateImage(Image &orig, int degree);
    void cropImage(Image  &orig, pair<int,int> st, pair<int,int> dimension);
    void resizeImage(Image &orig, int width, int height);
    void skew(Image &orig, float rad);
    void detectEdges(Image &orig, float alpha, int tresh);
    void blurImage(Image &orig, float alpha);
    void oilPainting(Image &orig, int radius, int intensityLevel);
    void addSolidFrame(Image &orig, double thickness);
    void addBee(Image &orig, double thickness);
};