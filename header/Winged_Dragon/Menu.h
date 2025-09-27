#pragma once
#include "Filter.h"
#include <iostream>
#include <exception>
#include <limits>
#include <string>
#include <iomanip>
/*
    Ready
    1-SAVE
    2-LOAD
    3-BACK
    4-GRAY
    5-BLACK_WHITE
    7-MERGE
    8-FLIP
    10-BRIGHTNESS
    11-CROP
    13-RESIZE
    15-CONTRAST
*/
class Menu {
    private:
        Filter applyFilter;
        Image img;
        std::string path = "image/";
        std::string name = "";
        enum TYPE {
            SAVE = 1,
            LOAD,
            BACK,
            GRAY,
            BLACK_WHITE, 
            INVERT, 
            MERGE, 
            FLIP, 
            ROTATE,
            BRIGHTNESS,
            CROP,
            DETECT_EDGES,
            RESIZE,
            BLUR,
            CONTRAST
        };

        void clear();
        void pause();
        bool invalidChoice(int option, int max, const std::string &message);
        void centerize(const std::string &menuName, int width);
        void printStart();
        void printFilter();

    public:
        void startMenu(); // first menu
        bool loadImage(Image& orig, std::string& origName);
        void filterMenu();
        void saveImage();
        void mergeImage();
        void flipImage();
        void rotateImage();
        void brightness();
        void cropImage();
        void detectEdges();
        void resizeImage();
        void blurImage();
        void contrast();
};