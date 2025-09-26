#include "Winged_Dragon/Filter.h"
#include <string>
using namespace std;

int main(){
    Image h;
    cout << "Enter Name: ";
    string name; cin >> name;
    h.loadNewImage("image/"+name);
    Filter temp;
    cout << "Enter alpha, t: ";
    double alpha;
    int thresh;
    cin >> alpha >> thresh;
    temp.detectEdges(h,alpha,thresh);
    h.saveImage("image/test.jpg");
    cout << "Done\n";
    return 0;
}