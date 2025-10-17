#ifndef OVERLAY_H
#define OVERLAY_H

#include "image_class.h"
#include "transformoperations.h"
class Overlay{
private:
    TransformOperations tf;
public:
    Overlay() = default;
    ~Overlay() = default;

    void addFrame(Image &orig, Image &frame, int r, int g, int b);
};

#endif // OVERLAY_H
