#pragma once
#include "Filter.h"
#include <iostream>
#include <exception>
#include <limits>
#include <string>
#include <iomanip>

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