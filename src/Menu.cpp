#include "Winged_Dragon/Menu.h"

using namespace std;

void Menu::clear()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Menu::pause() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Menu::printStart()
{
    cout << "1: Load Image\n2: Exit\n";
}

void Menu::printFilter()
{
    cout << "1: Save\n2: Back\n";
    cout << "3: Gray Filter\n4: Black and White Filter\n";
    cout << "5: Invert Filter\n6: Merge Filter\n";
    cout << "7: Flip Filter\n8: Rotate Filter\n";
    cout << "9: Brightness Filter\n10: Crop Filter\n";
    cout << "11: Detect Edges\n12: Resize Filter\n";
    cout << "13: Blur Filter\n14: Contrast\n\n";
}

void Menu::startMenu() {

    while (true) {
        printStart();
        int option;
        cout << "Choose Option: ";
        cin >> option;
    
        if(cin.fail() || option > 2 || option < 1) {
            clear();
            cout << "Input must be from options\n";
            pause();
            continue;
        }
    
        switch (option)
        {
        case 1:
            if(loadImage()) {
                filterMenu();
                cout << "RETURNED SUCCESSFULLY\n";
                pause();
            } else {
                pause();
                continue;
            }
            break;
        
        case 2:
            cout << "Good Bye\n";
            return;
        }
    }
    
}

bool Menu::loadImage() {
    string name;
    cout << "Enter image name with extension: ";
    cin >> name;
    try {
        img.loadNewImage(path+name);
    }
    catch(const exception& e) {
        cout << e.what() << '\n';
        return false;
    }

    cout << "LOADED SUCCESSFULLY\n";
    pause();
    cout << "\n\n";

    return true;
}

void Menu::filterMenu() {
    
    while(true) {

        printFilter();
    
        int option;
        cout << "Enter Option: ";
        cin >> option;
    
        if(cin.fail() || option > 14 || option < 1) {
            clear();
            cout << "Input must be from options\n";
            pause();
            continue;
        }
    
        switch (option)
        {
        case SAVE:
            saveImage();
            break;
    
        case BACK:
            return;
    
        case GRAY:
            applyFilter.grayScale(img);
            cout << "DONE SUCCESSFULLY\n";
            break;
    
        case BLACK_WHITE:
            applyFilter.blackWhite(img);
            cout << "DONE SUCCESSFULLY\n";
            break;
    
        case INVERT:
            applyFilter.invertImage(img);
            cout << "DONE SUCCESSFULLY\n";
            break;
    
        case MERGE:
            mergeImage();
            break;
    
        case FLIP:
            flipImage();
            break;
    
        case ROTATE:
            rotateImage();
            break;
    
        case BRIGHTNESS:
            brightness();
            break;
    
        case CROP:
            cropImage();
            break;
    
        case DETECT_EDGES:
            detectEdges();
            break;
    
        case RESIZE:
            resizeImage();
            break;
    
        case BLUR:
            blurImage();
            break;
    
        case CONTRAST:
            contrast();
            break;
        }
        pause();
    }
}

void Menu::saveImage() {
    cout << "Enter name of the new image with extension: ";
    string name; cin >> name;
    try {
        img.saveImage(path+name);
    }
    catch(const exception& e)
    {
       cout << e.what() << '\n';
       return;
    }

    cout << "SAVED SUCCESSFULLY\n";
}