#include "Winged_Dragon/Menu.h"
#include "Winged_Dragon/Menu.h"

void Menu::clear() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Menu::pause() {
    system("pause");
}

bool Menu::invalidChoice(int option, int mx, const string &message, int mn) {
    if (cin.fail() || option < mn || option > mx) {
        clear();
        cerr << message << "\n";
        pause();
        cout << "\n\n";
        return true;
    }
    return false;
}

void Menu::centerize(const string &menuName, int width) {
    int spaces = max(0, (int) (width - menuName.size()) / 2);
    cout << string(spaces, ' ') << menuName << "\n";
}

void Menu::printStart() {
    cout << '\n' << string(37, '=') << '\n';
    centerize("== Start Menu ==", 37);
    cout << string(37, '=') << '\n';
    cout << left << setw(3) << 1 << " : Load Image\n";
    cout << left << setw(3) << 2 << " : Exit\n\n";
}

void Menu::printFilter() {
    cout << '\n' << string(37, '=') << '\n';
    centerize("== File Options ==", 37);
    cout << string(37, '=') << '\n';
    cout << left << setw(3) << 1 << " : Save Image\n";
    cout << left << setw(3) << 2 << " : Load new Image\n";
    cout << left << setw(3) << 3 << " : Back\n";
    cout << left << setw(3) << 4 << " : Undo\n";
    cout << left << setw(3) << 5 << " : Redo\n";
    cout << '\n' << string(37, '=') << '\n';
    centerize("== Filter ==", 37);
    cout << string(37, '=') << '\n';
    cout << left << setw(3) << 6 << " : Gray\n";
    cout << left << setw(3) << 7 << " : BW\n";
    cout << left << setw(3) << 8 << " : Invert\n";
    cout << left << setw(3) << 9 << " : Merge\n";
    cout << left << setw(3) << 10 << " : Flip\n";
    cout << left << setw(3) << 11 << " : Rotate\n";
    cout << left << setw(3) << 12 << " : Brightness\n";
    cout << left << setw(3) << 13 << " : Crop\n";
    cout << left << setw(3) << 14 << " : Detect Edges\n";
    cout << left << setw(3) << 15 << " : Resize\n";
    cout << left << setw(3) << 16 << " : Blur\n";
    cout << left << setw(3) << 17 << " : Contrast\n";
    cout << left << setw(3) << 18 << " : Purple\n";
    cout << left << setw(3) << 19 << " : Infrared\n";
    cout << left << setw(3) << 20 << " : Sun\n";
    cout << left << setw(3) << 21 << " : Tv\n";
    cout << left << setw(3) << 22 << " : Solid ColorFrame\n";
    cout << left << setw(3) << 23 << ": Alternating Colors Frame\n\n";
}

bool Menu::backContinue() {
    cout << setw(3) << 1 << " : Continue\n";
    cout << setw(3) << 2 << " : Back\n\n";
    int op;
    cout << "Enter option: ";
    cin >> op;

    if (invalidChoice(op, 2, "Input must be from options", 1)) {
        return true;
    }

    if (op == 2) {
        cout << "Return successfuly\n\n";
        pause();
        return true;
    }

    return false;
}

void Menu::putToUndo() {
    undo.push(this->img);
    while (!redo.empty()) {
        redo.pop();
    }
}

void Menu::startMenu() {
    while (true) {
        printStart();
        int option;
        cout << "Choose Option: ";
        cin >> option;


        if (invalidChoice(option, 2, "Input must be from options", 1)) {
            continue;
        }

        switch (option) {
            case 1:
                if (loadImage(this->img, this->name)) {
                    pause();
                    filterMenu();
                    cout << "Returned successfully\n";
                    pause();
                    cout << "\n\n";
                } else {
                    pause();
                    cout << "\n\n";
                    continue;
                }
                break;

            case 2:
                cout << "Goodbye\n\n";
                return;
        }
    }

}

bool Menu::loadImage(Image &orig, string &origName) {

    cout << setw(3) << 1 << " : Continue\n";
    cout << setw(3) << 2 << " : Back\n\n";
    int op;
    cout << "Enter option: ";
    cin >> op;

    if (cin.fail() || op < 1 || op > 2) {
        clear();
        cerr << "Input must be from options" << "\n";
        cout << "\n\n";
        return false;
    }

    if (op == 2) {
        cout << "Return successfuly\n\n";
        return false;
    }

    cout << "Enter image name with extension: ";
    cin >> origName;

    try {
        orig.loadNewImage(path + origName);
    }
    catch (const exception &e) {
        cerr << e.what() << "\n";
        return false;
    }

    cout << "Loaded successfully\n";
    cout << "\n\n";

    return true;
}

void Menu::filterMenu() {

    while (true) {

        printFilter();

        int option;
        cout << "Enter Option: ";
        cin >> option;


        if (invalidChoice(option, 23, "Input must be from options", 1)) {
            continue;
        }

        switch (option) {
            case SAVE:
                saveImage();
                break;

            case LOAD:
                loadImage(this->img, this->name);
                pause();
                break;

            case BACK:
                return;

            case UNDO:
                xdoF(this->undo, this->redo, "No more actions to undo!\n");
                break;

            case REDO:
                xdoF(this->redo, this->undo, "No more actions to redo!\n");
                break;

            case GRAY:
                grayScale();
                break;

            case BLACK_WHITE:
                blackWhite();
                break;

            case INVERT:
                invertImage();
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

            case PURPLE:
                purbleFilter();
                break;

            case INFRARED:
                infraredFilter();
                break;
            case SUN:
                sun();
                break;
            case TV:
                tv();
                break;
            case SOLID_FRAME:
                addSolidFrame();
                break;
            case ALT_FRAME:
                addBee();
                break;
        }
        cout << "\n\n";
    }
}

void Menu::saveImage() {
    if (backContinue()) {
        return;
    }

    cout << setw(3) << 1 << " : Save to current image\n";
    cout << setw(3) << 2 << " : Save as new image\n\n";

    int option;
    cout << "Enter option: ";
    cin >> option;

    if (invalidChoice(option, 2, "Input must be from options", 1)) {
        return;
    }

    if (option == 1) {
        this->img.saveImage(path + name);
        cout << "SAVED SUCCESSFULLY\n";
        pause();
        return;
    }
    cout << "Enter name of the new image with extension: ";
    string newName;
    cin >> newName;

    try {
        img.saveImage(path + newName);
    }
    catch (const exception &e) {
        cerr << e.what() << "\n";
        pause();
        return;
    }

    cout << "SAVED SUCCESSFULLY\n";
    pause();
}

void Menu::grayScale() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    applyFilter.grayScale(this->img);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::blackWhite() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    applyFilter.blackWhite(this->img);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::invertImage() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    applyFilter.invertImage(this->img);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::mergeImage() {
    if (backContinue()) {
        return;
    }
    string newName;
    Image merged;
    int x = 1, y = 1;
    if (!loadImage(merged, newName)) {
        pause();
        return;
    }
    cout << setw(3) << 1 << " : Resize both to max width and height\n";
    cout << setw(3) << 2 << " : Get the common area\n\n";

    cout << "Enter Option: ";
    int option;
    cin >> option;

    if (invalidChoice(option, 2, "Input must be from options", 1)) {
        return;
    }

    int transparency;

    cout << "Enter Transparency of first image(integer between [0,100]): ";
    cin >> transparency;


    if (invalidChoice(transparency, 100, "Input must be integer between [0,100]", 1)) {
        return;
    }

    if (option == 2) {


        cout << "Enter the top-left coordinates where you want to place the new image\n";
        cout << "Enter x(integer between [1," << this->img.width << "]) : ";
        cin >> x;

        string msg1 = "x must be integer between [1," + to_string(this->img.width) + "]";
        string msg2 = "y must be integer between [1," + to_string(this->img.height) + "]";
        if (invalidChoice(x, this->img.width, msg1, 1)) {
            return;
        }
        cout << "Enter y(integer between [1," << this->img.height << "]) : ";
        cin >> y;

        if (invalidChoice(y, this->img.height, msg2, 1)) {
            return;
        }
    }

    putToUndo();
    applyFilter.mergeImage(this->img, merged, option, transparency, x - 1, y - 1);

    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::flipImage() {
    if (backContinue()) {
        return;
    }
    cout << left << setw(3) << 1 << " : Horizontal\n";
    cout << left << setw(3) << 2 << " : Vertical\n\n";
    cout << "Enter option: ";
    int option;
    cin >> option;

    if (invalidChoice(option, 2, "Input must be from options", 1)) {
        return;
    }
    bool horiz = (option == 1 ? true : false);
    putToUndo();
    applyFilter.flipImage(this->img, horiz);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::rotateImage() {
    if (backContinue()) {
        return;
    }
    cout << "Enter degree (must be divisible by 90): ";
    int degree;
    cin >> degree;
    if (invalidChoice(degree, INT_MAX, "Input must be integer", INT_MIN)) {
        return;
    }
    int n = (-degree + 359) / 360;
    if (degree < 0) degree += n * 360;

    if (degree % 90 != 0) {
        cerr << "Input must be divisible by 90\n\n\n";
        pause();
        return;
    }
    putToUndo();
    applyFilter.rotateImage(this->img, degree);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::brightness() {
    if (backContinue()) {
        return;
    }
    cout << "Enter percentage[-100,100]: ";
    int option;
    cin >> option;

    if (invalidChoice(option, 100, "Input must be integer from range [-100,100]", -100)) {
        return;
    }
    putToUndo();
    applyFilter.darkenLightn(this->img, option);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::cropImage() {
    if (backContinue()) {
        return;
    }
    cout << "Enter the top left point\n";
    cout << "Enter x: ";
    int x, y;
    cin >> x;

    string msg1 = "x must be integer between [1," + to_string(this->img.width) + "]";
    string msg2 = "y must be integer between [1," + to_string(this->img.height) + "]";
    if (invalidChoice(x, this->img.width, msg1, 1)) {
        return;
    }
    cout << "Enter y: ";
    cin >> y;

    if (invalidChoice(y, this->img.height, msg2, 1)) {
        return;
    }
    int width, height;
    cout << "Enter width: ";
    cin >> width;

    if (invalidChoice(width, this->img.width - x + 1, "Invalid width", 1)) {
        return;
    }
    cout << "Enter height: ";
    cin >> height;

    if (invalidChoice(height, this->img.height - y + 1, "Invalid width", 1)) {
        return;
    }

    putToUndo();
    applyFilter.cropImage(this->img, {x - 1, y - 1}, {width, height});
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::detectEdges() {
    if (backContinue()) {
        return;
    }
    int percent;
    cout << "Enter Edge sharpness[0,100]: ";
    cin >> percent;
    if (invalidChoice(percent, 100, "Input must be integer from range [0,100]", 0)) {
        return;
    }
    int threshhold = 120 - 0.9 * percent;

    putToUndo();
    applyFilter.detectEdges(this->img, 2.5, threshhold);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::resizeImage() {
    if (backContinue()) {
        return;
    }
    cout << "Enter new width: ";
    int width;
    cin >> width;

    if (invalidChoice(width, INT_MAX, "Invalid width", 1)) {
        return;
    }
    cout << "Enter new height: ";
    int height;
    cin >> height;

    if (invalidChoice(height, INT_MAX, "Invalid height", 1)) {
        return;
    }

    putToUndo();
    applyFilter.resizeImage(this->img, width, height);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::blurImage() {
    if (backContinue()) {
        return;
    }
    cout << "Enter percentage[0,100]: ";
    int percent;
    cin >> percent;

    if (invalidChoice(percent, 100, "Input must be integer from range [0,100]", 0)) {
        return;
    }
    float sigma = (15.0f * percent) / 100.0f;

    putToUndo();
    applyFilter.blurImage(this->img, sigma);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::contrast() {
    if (backContinue()) {
        return;
    }
    cout << "Enter percentage[-100,100]: ";
    int option;
    cin >> option;

    if (invalidChoice(option, 100, "Input must be integer from range [-100,100]", -100)) {
        return;
    }

    putToUndo();
    applyFilter.contrast(this->img, option);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::xdoF(stack<Image> &st, stack<Image> &en, const string &msg) {
    if (st.empty()) {
        cout << msg << '\n';
        pause();
        return;
    }
    en.push(this->img);
    this->img = st.top();
    st.pop();
    cout << "DONE SUCCESSFULLY\n";
}

void Menu::purbleFilter() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    applyFilter.purbleFilter(this->img);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::infraredFilter() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    cout << "Enter percentage: ";
    int op;
    cin >> op;
    if (invalidChoice(op, 100, "Enter integer between 0 to 100", 0)) {
        return;
    }
    applyFilter.infraredFilter(this->img, op / 100.0f);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::sun() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    cout << "Enter percentage: ";
    int op;
    cin >> op;
    if (invalidChoice(op, 100, "Enter integer between 0 to 100", 0)) {
        return;
    }
    applyFilter.sun(this->img, op / 100.0f);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::tv() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    applyFilter.tv(this->img);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}


void Menu::addSolidFrame() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    cout << "Enter percentage: ";
    int op;
    cin >> op;
    if (invalidChoice(op, 100, "Enter integer between 0 to 100", 0)) {
        return;
    }
    op = 100 - op;
    applyFilter.addSolidFrame(this->img, min(img.height, img.width) / op);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::addBee() {
    if (backContinue()) {
        return;
    }
    putToUndo();
    cout << "Enter percentage: ";
    int op;
    cin >> op;
    if (invalidChoice(op, 100, "Enter integer between 0 to 100", 0)) {
        return;
    }
    op = 100 - op;
    applyFilter.addBee(this->img, min(img.height, img.width) / op);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}





