#include "Winged_Dragon/Menu.h"

using namespace std;

void Menu::clear()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Menu::pause() {
    system("pause");
}

bool Menu::invalidChoice(int option, int mx, const string &message, int mn)
    {
        if (cin.fail() || option < mn || option > mx)
        {
            clear();
            cerr << message << "\n";
            pause();
            cout << "\n\n";
            return true;
        }
        return false;
    }

void Menu::centerize(const string &menuName, int width) {
    int spaces = max(0,(int)(width - menuName.size()) / 2);
    cout << string(spaces, ' ') << menuName << "\n";
}

void Menu::printStart()
{
    cout << '\n' << string(37,'=') << '\n';
    centerize("== Start Menu ==", 37);
    cout << string(37,'=') << '\n';
    cout << left << setw(3) << 1 <<" : Load Image\n";
    cout << left << setw(3) << 2 <<" : Exit\n\n";
}

void Menu::printFilter()
{
    cout << '\n' << string(37,'=') << '\n';
    centerize("== File Options ==", 37);
    cout << string(37,'=') << '\n';
    cout << left << setw(3) << 1 << " : Save Image\n";
    cout << left << setw(3) << 2 << " : Load new Image\n";
    cout << left << setw(3) << 3 << " : Back\n";
    cout << '\n' << string(37,'=') << '\n';
    centerize("== Filter ==", 37);
    cout << string(37,'=') << '\n';
    cout << left << setw(3) << 4 << " : Gray Filter\n";
    cout << left << setw(3) << 5 << " : Black and White Filter\n";
    cout << left << setw(3) << 6 << " : Invert Filter\n";
    cout << left << setw(3) << 7 << " : Merge Filter\n";
    cout << left << setw(3) << 8 << " : Flip Filter\n";
    cout << left << setw(3) << 9 << " : Rotate Filter\n";
    cout << left << setw(3) << 10 << " : Brightness Filter\n";
    cout << left << setw(3) << 11 << " : Crop Filter\n";
    cout << left << setw(3) << 12 <<" : Detect Edges\n";
    cout << left << setw(3) << 13 << " : Resize Filter\n";
    cout << left << setw(3) << 14 << " : Blur Filter\n";
    cout << left << setw(3) << 15 << " : Contrast\n\n";
}

void Menu::startMenu() {

    while (true) {
        printStart();
        int option;
        cout << "Choose Option: ";
        cin >> option;
        

        if(invalidChoice(option,2,"Input must be from options",1)) {
            continue;
        }
    
        switch (option)
        {
        case 1:
            if(loadImage(this->img, this->name)) {
                pause();
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
        cerr << e.what() << "\n";
        return false;
    }

    cout << "LOADED SUCCESSFULLY\n";
    cout << "\n\n";

    return true;
}

void Menu::filterMenu() {
    
    while(true) {

        printFilter();
    
        int option;
        cout << "Enter Option: ";
        cin >> option;
        

        if(invalidChoice(option,15,"Input must be from options",1)) {
            continue;
        }
    
        switch (option)
        {
        case SAVE:
            saveImage();
            break;

        case LOAD:
            loadImage(this->img, this->name);
            pause();
            break;
    
        case BACK:
            return;
    
        case GRAY:
            applyFilter.grayScale(this->img);
            cout << "DONE SUCCESSFULLY\n";
            pause();
            break;
    
        case BLACK_WHITE:
            applyFilter.blackWhite(this->img);
            cout << "DONE SUCCESSFULLY\n";
            pause();
            break;
    
        case INVERT:
            applyFilter.invertImage(this->img);
            cout << "DONE SUCCESSFULLY\n";
            pause();
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
        cout << "\n\n";
    }
}

void Menu::saveImage() {
    cout << "Option 1: Save on current image\nOption 2: Make new image\n\n";
    int option;
    cout << "Enter option: ";
    cin >> option;
    
    if(invalidChoice(option,2,"Input must be from options",1)) {
        return;
    }

    if(option == 1) {
        this->img.saveImage(path+name);
        cout << "SAVED SUCCESSFULLY\n";
        pause();
        return;
    }
    cout << "Enter name of the new image with extension: ";
    string newName; cin >> newName;
    
    try {
        img.saveImage(path+newName);
    }
    catch(const exception& e)
    {
       cerr << e.what() << "\n";
       pause();
       return;
    }

    cout << "SAVED SUCCESSFULLY\n";
    pause();
}
void Menu::mergeImage() {
    string newName;
    Image merged;
    int x = 1, y = 1;
    if(!loadImage(merged, newName)) {
        pause();
        return;
    }
    cout << "Option 1: Resize both to max width and height\nOption 2: Get the common area\n\n";
    
    cout << "Enter Option: ";
    int option; 
    cin >> option;
    
    if(invalidChoice(option,2,"Input must be from options",1)) {
        return;
    }

    int transparency;

    cout << "Enter Transparency of first image(integer betweem [0,100]): ";
    cin >> transparency;
    

    if(invalidChoice(transparency,100,"Input must be integer between [0,100]",1)) {
        return;
    }

    if (option == 2) {
    
    
        cout << "Enter the top left where you want to drag the new image\n";
        cout << "Enter x(inteher between [1," << this->img.width << "]) : ";
        cin >> x;
        
        string msg1 = "x must be integer between [1," + to_string(this->img.width) + "]"; 
        string msg2 = "y must be integer between [1," + to_string(this->img.height) + "]"; 
        if(invalidChoice(x,this->img.width,msg1,1)) {
            return;
        }
        cout << "Enter y(inteher between [1," << this->img.height << "]) : ";
        cin >> y;
        
        if(invalidChoice(y,this->img.height,msg2,1)) {
            return;
        }
    }

    applyFilter.mergeImage(this->img,merged,option,transparency,x-1,y-1);

    cout << "DONE SUCCESSFULLY\n";
    pause();
}
void Menu::flipImage()
{
    cout << left << setw(3) << 1 << " : Horizontal\n";
    cout << left << setw(3) << 2 << " : Vertical\n\n";
    cout << "Enter option: ";
    int option; cin >> option;
    
    if(invalidChoice(option,2,"Input must be from options",1)) {
        return;
    }
    bool horiz = (option == 1? true : false);
    applyFilter.flipImage(this->img,horiz);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::rotateImage()
{
    cout << "Enter degree (must be divisable by 90): ";
    int degree; cin >> degree;
    if(invalidChoice(degree,INT_MAX,"Input must be integer",INT_MIN)) {
        return;
    }
    int n = (-degree + 359)/360;
    if(degree < 0) degree += n * 360;

    if(degree%90 != 0) {
        cerr << "Input must be divisible by 90\n\n\n";
        return;
    }
    applyFilter.rotateImage(this->img, degree);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::brightness()
{
    cout << "Enter percentage[-100,100]: ";
    int option; cin >> option;
    
    if(invalidChoice(option,100,"Input must be integer from range [-100,100]", -100)) {
        return;
    }
    applyFilter.darkenLightn(this->img,option);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::cropImage()
{
    cout << "Enter the top left point\n";
    cout << "Enter x: ";
    int x,y;
    cin >> x;
    
    string msg1 = "x must be integer between [1," + to_string(this->img.width) + "]"; 
    string msg2 = "y must be integer between [1," + to_string(this->img.height) + "]"; 
    if(invalidChoice(x,this->img.width,msg1),1) {
        return;
    }
    cout << "Enter y: ";
    cin >> y;
    
    if(invalidChoice(y,this->img.height,msg2),1) {
        return;
    }
    int width, height;
    cout << "Enter width: ";
    cin >> width;
    
    if(invalidChoice(width,this->img.width - x + 1,"Invalid width"),1) {
        return;
    }
    cout << "Enter height: ";
    cin >> height;
    
    if(invalidChoice(height,this->img.height - y + 1,"Invalid width",1)) {
        return;
    }

    applyFilter.cropImage(this->img, {x-1,y-1}, {width,height});
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::detectEdges()
{
    int percent;
    cout << "Enter Edge sharpness[0,100]: ";
    cin >> percent;
    if(invalidChoice(percent,100,"Input must be integer from range [0,100]", 0)) {
        return;
    }
    int threshhold = 120 - 0.9 * percent;
    applyFilter.detectEdges(this->img,2.5,threshhold);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::resizeImage()
{
    cout << "Enter new width: ";
    int width;
    cin >> width;
    
    if(invalidChoice(width,INT_MAX,"Invalid width",1)) {
        return;
    }
    cout << "Enter new height: ";
    int height;
    cin >> height;
    
    if(invalidChoice(height,INT_MAX,"Invalid height",1)) {
        return;
    }

    applyFilter.resizeImage(this->img,width,height);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::blurImage()
{
    cout << "Enter percentage[0,100]: ";
    int percent; cin >> percent;
    
    if(invalidChoice(percent,100,"Input must be integer from range [0,100]", 0)) {
        return;
    }
    double sigma = (15.0 * percent) / 100.0;
    applyFilter.blurImage(this->img,sigma);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}

void Menu::contrast()
{
    cout << "Enter percentage[-100,100]: ";
    int option; cin >> option;
    
    if(invalidChoice(option,100,"Input must be integer from range [-100,100]", -100)) {
        return;
    }
    applyFilter.contrast(this->img,option);
    cout << "DONE SUCCESSFULLY\n";
    pause();
}