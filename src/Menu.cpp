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

bool Menu::invalidChoice(int option, int max, const string& message) {
    if(cin.fail() || option < 1 || option > max) {
        clear();
        cout << message << "\n";
        pause();
        cout << "\n\n";
        return true;
    }
    return false;
}

void Menu::printStart()
{
    cout << "1: Load Image\n2: Exit\n\n";
}

void Menu::printFilter()
{
    cout << "1 : Save\n2 : Load\n3 : Back\n";
    cout << "4 : Gray Filter\n5 : Black and White Filter\n";
    cout << "6 : Invert Filter\n7 : Merge Filter\n";
    cout << "8 : Flip Filter\n9 : Rotate Filter\n";
    cout << "10: Brightness Filter\n11: Crop Filter\n";
    cout << "12: Detect Edges\n13: Resize Filter\n";
    cout << "14: Blur Filter\n15: Contrast\n\n";
}

void Menu::startMenu() {

    while (true) {
        printStart();
        int option;
        cout << "Choose Option: ";
        cin >> option;

        if(invalidChoice(option,2,"Input must be from options")) {
            continue;
        }
    
        switch (option)
        {
        case 1:
            if(loadImage(this->img, this->name)) {
                filterMenu();
                cout << "RETURNED SUCCESSFULLY\n";
                pause();
                cout << "\n\n";
            } else {
                pause();
                cout << "\n\n";
                continue;
            }
            break;
        
        case 2:
            cout << "Good Bye\n\n";
            return;
        }
    }
    
}

bool Menu::loadImage(Image& orig, string& origName) {
    cout << "Enter image name with extension: ";
    cin >> origName;
    try {
        orig.loadNewImage(path+origName);
    }
    catch(const exception& e) {
        cout << e.what() << "\n";
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

        if(invalidChoice(option,15,"Input must be from options")) {
            continue;
        }
    
        switch (option)
        {
        case SAVE:
            saveImage();
            break;

        case LOAD:
            loadImage(this->img, this->name);
            break;
    
        case BACK:
            return;
    
        case GRAY:
            applyFilter.grayScale(this->img);
            cout << "DONE SUCCESSFULLY\n";
            break;
    
        case BLACK_WHITE:
            applyFilter.blackWhite(this->img);
            cout << "DONE SUCCESSFULLY\n";
            break;
    
        case INVERT:
            applyFilter.invertImage(this->img);
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
        cout << "\n\n";
    }
}

void Menu::saveImage() {
    cout << "Option 1: Save on current image\nOption 2: Make new image\n\n";
    int option;
    cout << "Enter option: ";
    cin >> option;

    if(cin.fail() || option > 2 || option < 1) {
            clear();
            cout << "Input must be from options\n";
            pause();
            return;
    }

    if(option == 1) {
        this->img.saveImage(path+name);
        return;
    }
    cout << "Enter name of the new image with extension: ";
    string newName; cin >> newName;
    try {
        img.saveImage(path+newName);
    }
    catch(const exception& e)
    {
       cout << e.what() << "\n";
       return;
    }

    cout << "SAVED SUCCESSFULLY\n";
}
void Menu::mergeImage() {
    string newName;
    Image merged;
    if(!loadImage(merged, newName)) {
        pause();
        return;
    }
    cout << "Option 1: Resize both to max width and height\n Option 2: Get the common area\n\n";
    
    cout << "Enter Option: ";
    int option; 
    cin >> option;
    
    if(invalidChoice(option,2,"Input must be from options")) {
        return;
    }

    int transparency;

    cout << "Enter Transparency of first image: ";
    cin >> transparency;

    if(invalidChoice(transparency,100,"Input must be integer between [0,100]")) {
        return;
    }

    applyFilter.mergeImage(this->img,merged,option,transparency,0,0);

    cout << "DONE SUCCESSFULLY\n";
}
void Menu::flipImage()
{
}

void Menu::rotateImage()
{
}

void Menu::brightness()
{
}

void Menu::cropImage()
{
}

void Menu::detectEdges()
{
}

void Menu::resizeImage()
{
}

void Menu::blurImage()
{
}

void Menu::contrast()
{
}
