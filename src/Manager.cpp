#include "Winged_Dragon/Manager.h"

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

void Manager::infraredFilter(Image &orig, float percent)
{
    color.infraredFilter(orig, percent);
}

void Manager::sun(Image &orig, int percent)
{
    color.sun(orig, percent);
}

void Manager::tv(Image &orig)
{
    color.tv(orig);
}

void Manager::mergeImage(Image &orig, Image &merged, int option, int transparency, int startX, int startY)
{
    transform.mergeImage(orig, merged, option, transparency, startX, startY);
}

void Manager::flipImage(Image &orig, bool &horiz)
{
    transform.flipImage(orig, horiz);
}

void Manager::rotateImage(Image &orig, int degree)
{
    transform.rotateImage(orig, degree);
}

void Manager::cropImage(Image &orig, pair<int, int> st, pair<int, int> dimension)
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

void Manager::detectEdges(Image &orig, float alpha, int tresh)
{
    art.detectEdges(orig, alpha, tresh);
}

void Manager::blurImage(Image &orig, float alpha)
{
    art.blurImage(orig, alpha);
}

void Manager::oilPainting(Image &orig, int radius, int intensityLevel)
{
    art.oilPainting(orig, radius, intensityLevel);
}

void Manager::addSolidFrame(Image &orig, double thickness)
{
    layer.addSolidFrame(orig, thickness);
}

void Manager::addBee(Image &orig, double thickness)
{
    layer.addBee(orig, thickness);
}