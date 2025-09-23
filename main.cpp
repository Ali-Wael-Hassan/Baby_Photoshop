#include "Winged_Dragon/Filter.h"
#include <cstdlib>
using namespace std;

int main(){
    Image h;
    cout << "Enter Name: ";
    string name; cin >> name;
    h.loadNewImage("image/"+name+".jpg");
    Image z(h);
    Image y(h);
    Image k(h);
    Filter temp;
    cout << "Enter Percentage: ";
    int x; cin >> x;
    temp.darkenLightn(h,x);
    temp.contrast(z,x);

    temp.blackWhite(y);
    h.saveImage("image/test1.jpg");
    z.saveImage("image/test2.jpg");
    y.saveImage("image/test3.jpg");
    cout << "Done\n";
    return 0;

}