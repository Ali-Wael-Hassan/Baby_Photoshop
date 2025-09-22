#include "Winged_Dragon/Filter.h"
#include <cstdlib>
using namespace std;

int main(){
    Image h;
    cout << "Enter Name: ";
    string name; cin >> name;
    h.loadNewImage("image/"+name+".jpg");
    Image z(h);
    Filter temp;
    cout << "Enter Percentage: ";
    int x; cin >> x;
    temp.darkenLightn(h,x);
    temp.contrast(z,x);
    h.saveImage("image/test.jpg");
    z.saveImage("image/test2.jpg");
    cout << "Done\n";
    return 0;
}
