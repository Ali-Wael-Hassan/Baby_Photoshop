#include "Winged_Dragon/Filter.h"

using namespace std;

int main(){
    Image h;
    cout << "Enter Name: ";
    string name; cin >> name;
    h.loadNewImage("image/"+name);
    Filter temp;
    temp.detectEdges(h);
    h.saveImage("image/test5.jpg");
    cout << "Done\n";
    return 0;
}