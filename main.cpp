#include "Winged_Dragon/Filter.h"
#include <cstdlib>
using namespace std;

int main(){
    Image h;
    h.loadNewImage("image/arrow.jpg");
    Filter temp;
    temp.blackWhite(h);
    h.saveImage("image/test.jpg");
    system("pause");
    return 0;
}
