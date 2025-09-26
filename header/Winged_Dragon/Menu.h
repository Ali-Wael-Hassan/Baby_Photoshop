#pragma once
#include "Filter.h"
#include <iostream>
#include <exception>

class Menu {
    private:
        Filter applyFilter;
        Image img;
        std::string path = "image/";
        enum TYPE {
            SAVE,
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
        void printStart();
        void printFilter();

    public:
        void startMenu(); // first menu
        bool loadImage();
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