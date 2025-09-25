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
    int size;
    cin >> alpha;
    for(int i = 20; i <= 254; ++i) {
        string name = "image/test";
        name += to_string(i);
        Image cpy(h);
        temp.detectEdges(cpy,alpha,i);
        cpy.saveImage(name+".jpg");
    }
    cout << "Done\n";
    return 0;
}