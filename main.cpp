#include "Winged_Dragon/Filter.h"
#include <string>
using namespace std;

int main(){
    Image h;
    cout << "Enter Name: ";
    string name; cin >> name;
    h.loadNewImage("image/"+name);
    Filter temp;
    cout << "Enter alpha: ";
    double alpha;
    int size; cin >> size;
    cin >> alpha;
    temp.blurImage(h,alpha,size);
    h.saveImage("image/test.jpg");
    cout << "Done\n";
    return 0;
}