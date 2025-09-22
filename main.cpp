#include "header/Winged_Dragon/Filter.h"
#include <cstdlib>
using namespace std;

int main(){
    Image h;
    Filter j;
    h.loadNewImage("image/toy1.jpg");
    j.cropImage(h,{700,700},{600,600});
    h.saveImage("image/testtoy1.jpg");
    system("pause");
    return 0;
}
