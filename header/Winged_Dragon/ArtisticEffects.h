#pragma once

#include "ToneAndColorAdjustments.h"

class ArtisticEffects {
private :
    ToneAndColorAdjustments apply;
public:
    // Constructor
    ArtisticEffects() = default;

    // Destructor
    ~ArtisticEffects() = default;

    void detectEdges(Image &orig, float alpha, int tresh);
    void generateKernel(std::vector<float>& kernel, float sigma);
    void blurImage(Image &orig, float alpha);
    void oilPainting(Image &orig, int radius, int intensityLevel);
};