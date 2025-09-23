#include "header/Winged_Dragon/Filter.h"
#include <cstdlib>
using namespace std;

int main(){
    Image h;
    Filter j;
    h.loadNewImage("image/luffy.jpg");
    int gg =1000,gb= 1000;
    j.blackWhite(h);
    h.saveImage("image/testluffy.jpg");
    system("pause");
    return 0;
}
