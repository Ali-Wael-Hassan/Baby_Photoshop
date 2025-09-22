#include "header/Winged_Dragon/Filter.h"
#include <cstdlib>
using namespace std;

int main(){
    Image h;
    Filter j;
    h.loadNewImage("image/toy1.jpg");
    int gg =1000,gb= 1000;
    j.resizeImage(h,gg,gb);
    h.saveImage("image/testtoy1.jpg");
    system("pause");
    return 0;
}
