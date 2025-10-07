#pragma once
#include "Manager.h"

using namespace std;
class Menu {
    private:
        Manager applyFilter;
        Image img;
        string path = "image/";
        string name = "";
        enum TYPE {
            SAVE = 1,
            LOAD,
            BACK,
            UNDO,
            REDO,
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
            CONTRAST,
            PURPLE,
            INFRARED,
            SUN,
            TV,
            SOLID_FRAME,
            ALT_FRAME,
            SKEW,
            OIL_PAINTING
        };
        stack<Image> undo, redo;
        void clear();
        void pause();
        bool invalidChoice(int option, int mx, const std::string &message, int mn = 1);
        void centerize(const std::string &menuName, int width);
        void printStart();
        void printFilter();
        bool backContinue();
        void putToUndo();

    public:
        void startMenu();
        bool loadImage(Image& orig, std::string& origName);
        void filterMenu();
        void saveImage();
        void grayScale();
        void blackWhite();
        void invertImage();
        void mergeImage();
        void flipImage();
        void rotateImage();
        void brightness();
        void cropImage();
        void detectEdges();
        void resizeImage();
        void blurImage();
        void contrast();
        void purbleFilter();
        void infraredFilter();
        void xdoF(stack<Image> &st, stack<Image> &en, const string &msg);
        void sun();
        void tv();
        void addSolidFrame();
        void addBee();
        void skew();
        void oilPainting();
};