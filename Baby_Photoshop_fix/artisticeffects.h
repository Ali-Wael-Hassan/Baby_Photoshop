#ifndef ARTISTICEFFECTS_H
#define ARTISTICEFFECTS_H

#include "toneandcoloradjustments.h"
#include <vector>

class ArtisticEffects {
private :
    ToneAndColorAdjustments apply;
public:
    // Constructor
    ArtisticEffects() = default;

    // Destructor
    ~ArtisticEffects() = default;

    void detectEdges(Image &orig, int threshold);
    void generateKernel(std::vector<float>& kernel, float sigma);
    void blurImage(Image &orig, float alpha);
    void boxBlur(Image &orig, int radius);
    void oilPainting(Image &orig, int radius, int intensityLevel);
};
#endif // ARTISTICEFFECTS_H
