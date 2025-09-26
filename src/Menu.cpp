#include "Winged_Dragon/Menu.h"
using namespace std;

void Menu::startMenu() {
    cout << "1: Load Image\n2: Exit\n";
    int option;
    cout << "Choose Option: ";
    cin >> option;

    if(cin.fail() || option > 2 || option < 1) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Input must be from options\n";
        system("pause");
        startMenu();
    }

    if(option == 1) {
        if(loadImage()) {
            filterMenu();
        }
        else {
            system("pause");
            startMenu();
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
    catch(exception e) {
        cout << e.what() << '\n';
        return false;
    }

    return true;
}

void Menu::filterMenu() {
    bool valid = true;
    cout << "1: Save\n2: Back\n3: Exit\n";
    cout << "4: Gray Filter\n5: Black and White Filter\n";
    cout << "6: Invert Filter\n7: Merge Filter\n";
    cout << "8: Flip Filter\n9: Rotate Filter\n";
    cout << "10: Brightness Filter\n11: Crop Filter\n";
    cout << "12: Detect Edges\n13: Resize Filter\n";
    cout << "14: Blur Filter\n15: Contrast\n\n";

    int option;
    cout << "Enter Option: ";
    cin >> option;

    if(cin.fail() || option > 16 || option < 1) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Input must be from options\n";
        system("pause");
        filterMenu();
    }

    switch (option)
    {
    case SAVE:
        saveImage();
        return;
        break;

    case BACK:
        startMenu();
        break;

    case EXIT:
        return;
        break;

    case GRAY:
        /* code */
        break;

    case BLACK_WHITE:
        /* code */
        break;

    case INVERT:
        applyFilter.invertImage(img);
        filterMenu();
        break;

    case MERGE:
        /* code */
        break;

    case FLIP:
        /* code */
        break;

    case ROTATE:
        /* code */
        break;

    case BRIGHTNESS:
        /* code */
        break;

    case CROP:
        /* code */
        break;

    case DETECT_EDGES:
        /* code */
        break;

    case RESIZE:
        /* code */
        break;

    case BLUR:
        /* code */
        break;

    case CONTRAST:
        /* code */
        break;
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
       filterMenu();
    }
}
