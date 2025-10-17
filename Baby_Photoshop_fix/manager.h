#ifndef MANAGER_H
#define MANAGER_H
#include "toneandcoloradjustments.h"
#include "artisticeffects.h"
#include "transformoperations.h"
#include "overlay.h"

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
    void infraredFilter(Image &orig);
    void sun(Image& orig, int percent);
    void tv(Image& orig);
    void mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int x1, int y1, int x2, int y2, int w, int h);
    void flipImage(Image &orig, bool& horiz);
    void rotateImage(Image &orig, int degree);
    void cropImage(Image  &orig, std::pair<int,int> st, std::pair<int,int> dimension);
    void resizeImage(Image &orig, int width, int height);
    void skew(Image &orig, float rad);
    void detectEdges(Image &orig, int threshold);
    void blurImage(Image &orig, float alpha);
    void oilPainting(Image &orig, int radius, int intensityLevel);
    void addFrame(Image &orig, Image &frame, int r, int g, int b);
    void boxBlur(Image &orig, int radius);
    void oldPhoto(Image &orig);
};

#endif // MANAGER_H
