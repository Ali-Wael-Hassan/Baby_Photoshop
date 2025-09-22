#include "header/Winged_Dragon/Filter.h"
#include <cstdlib>
using namespace std;

int main(){
    Image h,g;
    h.loadNewImage("image/arrow.jpg");
    g.loadNewImage("image/arrow.jpg");
    Filter temp1,temp2;
    bool horiz = true;
    bool nothoriz = false;
    temp1.invertImage(h,horiz);
    temp2.invertImage(g,nothoriz);
    h.saveImage("image/test.jpg");
    g.saveImage("image/test2.jpg");
    system("pause");
    return 0;
}
