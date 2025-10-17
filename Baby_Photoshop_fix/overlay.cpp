#include "overlay.h"

void Overlay::addFrame(Image &orig, Image &frame, int r, int g, int b) {
    tf.resizeImage(frame, orig.width, orig.height);
    Image result(orig.width, orig.height);

    for (int x = 0; x < orig.width; ++x) {
        for (int y = 0; y < orig.height; ++y) {
            bool isWhite =
                frame(x, y, 0) > 240 &&
                frame(x, y, 1) > 240 &&
                frame(x, y, 2) > 240;

            if (isWhite) {
                // Transparent region → keep original pixel
                result(x, y, 0) = orig(x, y, 0);
                result(x, y, 1) = orig(x, y, 1);
                result(x, y, 2) = orig(x, y, 2);
            } else {
                result(x, y, 0) = r;
                result(x, y, 1) = g;
                result(x, y, 2) = b;
            }
        }
    }

    std::swap(orig, result);
}
