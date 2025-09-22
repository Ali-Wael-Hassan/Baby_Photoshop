#include "Winged_Dragon/Filter.h"
#include <cstdlib>
using namespace std;

int main(){
    Image h;
    h.loadNewImage("image/building.jpg");
    Filter temp;
    cout << "Enter Percentage: ";
    int x; cin >> x;
    temp.darkenLightn(h,x);
    h.saveImage("image/test.jpg");
    cout << "Done\n";
    return 0;
}
