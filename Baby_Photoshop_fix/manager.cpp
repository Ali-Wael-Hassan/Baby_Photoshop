#include "manager.h"

void Manager::grayScale(Image &orig)
{
    color.grayScale(orig);
}

void Manager::blackWhite(Image &orig)
{
    color.blackWhite(orig);
}

void Manager::invertImage(Image &orig)
{
    color.invertImage(orig);
}

void Manager::darkenLightn(Image &orig, int percent)
{
    color.darkenLightn(orig, percent);
}

void Manager::contrast(Image &orig, int percent)
{
    color.contrast(orig, percent);
}

void Manager::purbleFilter(Image &orig)
{
    color.purbleFilter(orig);
}

void Manager::infraredFilter(Image &orig)
{
    color.infraredFilter(orig);
}

void Manager::sun(Image &orig, int percent)
{
    color.sun(orig, percent);
}

void Manager::tv(Image &orig)
{
    color.tv(orig);
}

void Manager::mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int x1, int y1, int x2, int y2, int w, int h)
{
    transform.mergeImage(orig, merged, option, transpaerncy, x1, y1, x2, y2, w, h);
}

void Manager::flipImage(Image &orig, bool &horiz)
{
    transform.flipImage(orig, horiz);
}

void Manager::rotateImage(Image &orig, int degree)
{
    transform.rotateImage(orig, degree);
}

void Manager::cropImage(Image &orig, std::pair<int, int> st, std::pair<int, int> dimension)
{
    transform.cropImage(orig, st, dimension);
}

void Manager::resizeImage(Image &orig, int width, int height)
{
    transform.resizeImage(orig, width, height);
}

void Manager::skew(Image &orig, float rad)
{
    transform.skew(orig, rad);
}

void Manager::detectEdges(Image &orig, int threshold)
{
    art.detectEdges(orig, threshold);
}

void Manager::blurImage(Image &orig, float alpha)
{
    art.blurImage(orig, alpha);
}

void Manager::oilPainting(Image &orig, int radius, int intensityLevel)
{
    art.oilPainting(orig, radius, intensityLevel);
}

void Manager::addFrame(Image &orig, Image &frame, int r, int g, int b)
{
    layer.addFrame(orig, frame, r, g, b);
}


void Manager::boxBlur(Image &orig, int radius) {
    art.boxBlur(orig, radius);
}

void Manager::oldPhoto(Image &orig) {
    color.oldPhoto(orig);
}
