#include "Winged_Dragon/Overlay.h"

void Overlay::addSolidFrame(Image &orig, double thickness) { // add(r, g, b sliders to play with the color of the frame
    int nw = orig.width + (2 * thickness);
    int nh = orig.height + (2 * thickness);

    Image framed(nw, nh);
    for (int y = 0; y < nh; ++y) {
        for (int x = 0; x < nw; ++x) {
            framed(x, y, 0) = 0;
            framed(x, y, 1) = 255;
            framed(x, y, 2) = 0;
        }
    }

    for (int y = 0; y < orig.height; ++y) {
        for (int x = 0; x < orig.width; ++x) {
            for (int c = 0; c < 3; ++c) {
                framed(x + thickness, y + thickness, c) = orig(x, y, c);
            }
        }
    }
    orig = framed;
}

void Overlay::addBee(Image &orig, double thickness) {
    int nw = orig.width + (2 * thickness);
    int nh = orig.height + (2 * thickness);

    Image framed(nw, nh);
    for (int y = 0; y < nh; ++y) {
        for (int x = 0; x < nw; ++x) {
            for (int i = 0; i < framed.channels; ++i) {
                framed(x, y, i) = 0;
            }
        }
    }
    if ((int) thickness == 0) thickness += 1;

    for (int by = 0; by < nh; by += (int) thickness) {
        for (int bx = 0; bx < nw; bx += (int) thickness) {
            if (((bx / (int) thickness) + (by / (int) thickness)) % 2 == 0) {
                for (int y = by; y < by + thickness && y < nh; ++y) {
                    for (int x = bx; x < bx + thickness && x < nw; ++x) {
                        framed(x, y, 0) = 255;
                        framed(x, y, 1) = 165;
                        framed(x, y, 2) = 0;
                    }
                }
            }
        }
    }

    for (int y = thickness; y < framed.height - thickness + 1; ++y) {
        for (int x = thickness; x < framed.width - thickness + 1; ++x) {
            for (int k = 0; k < orig.channels; ++k) {
                framed(x, y, k) = orig(x - thickness, y - thickness, k);
            }
        }
    }
    orig = framed;
}