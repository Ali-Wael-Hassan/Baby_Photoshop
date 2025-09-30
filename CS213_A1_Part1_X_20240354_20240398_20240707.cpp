/*
    Project : Baby Photoshop
    File    : CS213_A1_Part1_X_20240354_20240398_20240707.cpp
    Section : SX

    Team Members:
    - Ali Wael       (ID 20240354)  -> Gray Scale (1), Merge Image (4), Darken & Lighten (7), Detect Edges (10)
    - Amr Atif       (ID 20240398)  -> Black & White (2), Flip Image (5), Crop Image (8), Resize Image (11)
    - Yousef Hassib  (ID 20240707)  -> Invert Colors (3), Rotate Image (6), Blur Image (12)

    WARNING:
        you must make image folder to run the program correctly

    Description:
    The program starts with the main menu which has two options:
        1) Load Image
        2) Exit

    After loading the first image, the Filter Menu appears:
        == File Options == 
            - Save image
            - Load new image
            - Back to main menu
        == Filters ==
            - All filters listed above

    First Note: darkenLight is Darken and Lighten combined: 
          (-v) applies Darken and (+v) applies Lighten.
    
    Second Note: images must be put in folder in the main directory with name image example: image/myImg.jpg
    Third Note: put only name of the image + extension
*/

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdint>
#include <exception>
#include <limits>
#include <iomanip>
#include "Image_Class.h"
using namespace std;

#define vd vector<double>
#define vvd vector<vector<double>>

class Filter {
public:
    // Constructor
    Filter() = default;

    // Destructor
    ~Filter() = default;

    void grayScale(Image &orig); // Grayscale Conversion
    void blackWhite(Image &orig); // Black and White
    void invertImage(Image &orig); // Invert Images
    void mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int startX, int startY); // Merge Images
    void flipImage(Image &orig, bool& horiz); // Flip Image
    void rotateImage(Image &orig, int degree); // Rotate Image
    void darkenLightn(Image &orig, int percent); // Darken and Lighten Image
    void cropImage(Image  &orig, pair<int,int> st, pair<int,int> dimension);// Crop Image
    void detectEdges(Image &orig, double alpha, int tresh); // Detect Image Edges
    void resizeImage(Image &orig, int width, int height);
    void generateKernel(vector<double>& kernel, double sigma);
    void blurImage(Image &orig, double alpha); // Blur Image
    void contrast(Image &orig, int percent); // Adjust Contrast
};

// Ali Wael 20240354
void Filter::grayScale(Image &orig) {
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            int R = orig(x,y,0),
                G = orig(x,y,1),
                B = orig(x,y,2);
            
            int gray= min(0.299*R+0.587*G+0.114*B + 0.5, 255.0);

            for(int c = 0; c < orig.channels; ++ c) {
                orig(x,y,c) = gray;

            }
        }
    }
}

// Amr Atif 20240398
void Filter::blackWhite(Image &orig) {
        Filter temp;
        temp.grayScale(orig);
        for(int i = 0;i<orig.width;i++){
            for(int j = 0;j<orig.height;j++){
                for(int c = 0;c<orig.channels;c++){
                    orig(i,j,c)=((orig(i,j,c)>=128)? 255:0);
                }
            }
        }
}

// Youssef Mohamed Hassib 20240707
void Filter::invertImage(Image &orig) {
    for (int i = 0; i < orig.width; ++i) {
        for (int j = 0; j < orig.height; ++j) {
            orig(i, j, 0) = 255 - orig(i, j, 0);
            orig(i, j, 1) = 255 - orig(i, j, 1);
            orig(i, j, 2) = 255 - orig(i, j, 2);
        }
    }
}

// Ali Wael 20240354
void Filter::mergeImage(Image &orig, Image &merged, int option, int transpaerncy, int startX, int startY) {
    double dx = (double) transpaerncy / 100;
    int w;
    int h;

    if(option == 1) {
        w = max(orig.width, merged.width);
        h = max(orig.height, merged.height);
        resizeImage(orig,w,h);
        resizeImage(merged,w,h);
    } else {
        w = min(orig.width - startX, merged.width);
        h = min(orig.height - startY, merged.height);
        cropImage(orig,{startX,startY}, {w,h});
        cropImage(merged,{0,0}, {w,h});
    }

    // create Temp image    
    Image temp(w,h);

    for(int x = 0; x < w; ++x) {
        for(int y = 0; y < h; ++y) {
            for(int c = 0; c < temp.channels; ++c) {
                double val = (1-dx) * orig(x,y,c) + dx * merged(x,y,c);
                temp(x,y,c) = min(255.0, max(0.0,val));
            }
        }
    }

    orig = temp;
}

// Amr Atif 20240398
void Filter::flipImage(Image &orig, bool& horiz) {
    int l = 0;
    int r = (horiz) ? (orig.width - 1) : (orig.height - 1);
    int direction = (horiz) ? orig.height : orig.width;

    while (l < r) {
        for (int i = 0; i < direction; i++) {
            for (int c = 0; c < orig.channels; c++) {
                if (horiz)
                    std::swap(orig(l, i, c), orig(r, i, c));
                else
                    std::swap(orig(i, l, c), orig(i, r, c));
            }
        }
        l++;
        r--;
    }
}


//Youssef Mohamed Hassib 20240707
void Filter::rotateImage(Image &orig, int degree) {
    int n = degree / 90; // dependent on degree % 90 == 0, further updates to come to make it valid all 360 degrees
    while (n--) {
        Image res(orig.height, orig.width);
        for (int y = 0; y < orig.height; ++y) {
            for (int x = 0; x < orig.width; ++x) {
                for (int c = 0; c < orig.channels; ++c) {
                    res(orig.height - 1 - y, x, c) = orig(x, y, c);
                }
            }
        }
        orig = res;
    }

}

//Ali-Wael 20240354
void Filter::darkenLightn(Image &orig, int percent) {
    // percent -100 to 100
    double v = pow((double) std::abs(percent) / 100,1.5);
    
    bool dark = 0;
    if(percent < 0) dark = 1;
    
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                if(dark) orig(x,y,c) = max(0.0,(1-v) * orig(x,y,c));
                else orig(x,y,c) = min(255.0,(1+v) * orig(x,y,c));
            }
        }
    }
}

// Amr Atif 20240398
void  Filter::cropImage(Image  &orig, std::pair<int,int> st, std::pair<int,int> dimension) {
    Image temp(dimension.first, dimension.second); 
    for (int i = 0; i < dimension.first; i++) {           
        for (int j = 0; j < dimension.second; j++) {       
            for (int c = 0; c < orig.channels; c++) {
                temp(i, j, c) = orig(st.first + i, st.second + j, c);
            }
        }
    }
    orig = temp;
}

// Ali Wael 20240354
void Filter::detectEdges(Image &orig, double alpha, int tresh) {
    grayScale(orig);
    blurImage(orig, alpha);

    int w = orig.width;
    int h = orig.height;

    int g1[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int g2[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    double *arr = new double[w*h], mx = 0.0;

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            double sum1 = 0, sum2 = 0;
            
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    double val = orig(x + dx, y + dy, 0);
                    sum1 += val * g1[dy + 1][dx + 1];
                    sum2 += val * g2[dy + 1][dx + 1];
                }
            }
            
            double grad = sqrt(sum1 * sum1 + sum2 * sum2);

            arr[y * w + x] = grad;
        }
    }

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            int out = (arr[y * w + x] >= tresh? 0 : 255);
            for(int c = 0; c < orig.channels; ++c) {
                orig(x,y,c) = out;
            }
        }
    }

    delete [] arr;
}

// Amr Atif 20240398
void Filter::resizeImage(Image &orig, int width, int height) {
    Image temp(width, height);
    double sw = static_cast<double>(orig.width) / width;
    double sh = static_cast<double>(orig.height) / height;

    for (int j = 0; j < height; j++) {
        double sy = j * sh;
        int y = static_cast<int>(sy);
        double dy = sy - y;

        for (int i = 0; i < width; i++) {
            double sx = i * sw;
            int x = static_cast<int>(sx);
            double dx = sx - x;

            for (int c = 0; c < orig.channels; c++) {
                
                int x0 = min(orig.width-1,max(0,x));
                int x1 = min(orig.width-1,max(0,x+1));
                int y0 = min(orig.height-1,max(0,y));
                int y1 = min(orig.height-1,max(0,y+1));
                double top = orig(x0, y0, c) * (1 - dx) + orig(x1, y0, c) * dx;
                double bottom = orig(x0, y1, c) * (1 - dx) + orig(x1, y1, c) * dx;
                double val = top * (1 - dy) + bottom * dy;

                temp(i, j, c) = static_cast<uint8_t>(min(255.0,max(0.0,val)));
            }
        }
    }

    orig = temp;
}

// Youssef Mohamed Hassib 20240707
void Filter::generateKernel(vd& kernel, double sigma) { // generates the kernel used to blur efficiently
    int radius = ceil(3 * sigma);
    int size = 2 * radius + 1;
    kernel.assign(size, 0.0);

    double sum = 0;
    double PI = acos(-1.0);

    for (int x = -radius; x <= radius; ++x) {
        double G = exp(-(x * x) / (2 * sigma * sigma)) / (2 * PI * sigma * sigma);
        kernel[x + radius] = G;
        sum += G;
    }

    for (int x = 0; x < size; ++x)
        kernel[x] /= sum;
}

// Youssef Mohamed Hassib 20240707
void Filter::blurImage(Image &orig, double alpha) {
    if(alpha < 1e-9) return;
    vd kernel;
    generateKernel(kernel, alpha);
    int half = kernel.size() / 2;
    Image temp(orig);
    // Blurring horizontally (1D)
    for (int y = 0; y < temp.height; ++y) {
        for (int x = 0; x < temp.width; ++x) {
            for (int c = 0; c < temp.channels; ++c) {
                double val = 0;
                for (int dk = -half; dk <= half; ++dk) {
                    int x2 = max(0, min(x + dk, temp.width - 1));
                    val += orig(x2, y, c) * kernel[dk + half];
                }
                temp(x, y, c) = min(255.0, max(val, 0.0));
            }
        }
    }

    orig = temp;
    // Blurring vertically (1D)
    for (int y = 0; y < temp.height; ++y) {
        for (int x = 0; x < temp.width; ++x) {
            for (int c = 0; c < temp.channels; ++c) {
                double val = 0;
                for (int dk = -half; dk <= half; ++dk) {
                    int y2 = max(0, min(y + dk, temp.height - 1));
                    val += orig(x, y2, c) * kernel[dk + half];
                }

                temp(x, y, c) = min(255.0, max(val, 0.0));
            }
        }
    }
    orig = temp;
}

// Ali-Wael 20240354
void Filter::contrast(Image &orig, int percent){ 
    // -100 to 100
    double v = 1.0 + (double) percent / 100;
    if(percent >= 0) v = 1.0 + (double) percent / 100;
    else v = 1.0 + (double) percent / 200;
    
    for(int x = 0; x < orig.width; ++x) {
        for(int y = 0; y < orig.height; ++y) {
            for(int c = 0; c < orig.channels; ++c) {
                double val = (orig(x,y,c)-128.0) * v + 128.0;
                val = max(0.0,min(255.0,val));
                orig(x,y,c) = val;
            }
        }
    }
}

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
        bool invalidChoice(int option, int mx, const std::string &message, int mn = 1);
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

void Menu::clear()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Menu::pause() {
    system("pause");
}

bool Menu::invalidChoice(int option, int mx, const string &message, int mn) {
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

    cout << "Loaded successfully\n";
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
    cout << "Option 1: Save to current image\nOption 2: Save as new image\n\n";
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

    cout << "Enter Transparency of first image(integer between [0,100]): ";
    cin >> transparency;
    

    if(invalidChoice(transparency,100,"Input must be integer between [0,100]",1)) {
        return;
    }

    if (option == 2) {
    
    
        cout << "Enter the top-left coordinates where you want to place the new image\n";
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
    cout << "Enter degree (must be divisible by 90): ";
    int degree; cin >> degree;
    if(invalidChoice(degree,INT_MAX,"Input must be integer",INT_MIN)) {
        return;
    }
    int n = (-degree + 359)/360;
    if(degree < 0) degree += n * 360;

    if(degree%90 != 0) {
        cerr << "Input must be divisible by 90\n\n\n";
        pause();
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
    if(invalidChoice(x,this->img.width,msg1,1)) {
        return;
    }
    cout << "Enter y: ";
    cin >> y;
    
    if(invalidChoice(y,this->img.height,msg2,1)) {
        return;
    }
    int width, height;
    cout << "Enter width: ";
    cin >> width;
    
    if(invalidChoice(width,this->img.width - x + 1,"Invalid width",1)) {
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


int main(){
    cout << string(45,'=') << '\n';
    string menuName = "== Welcome to Baby Photoshop ==";
    int spaces = max(0,(int)(45 - menuName.size()) / 2);
    cout << string(spaces, ' ') << menuName << "\n";
    cout << string(45,'=') << "\n\n\n\n";
    Menu run;
    run.startMenu();
}
