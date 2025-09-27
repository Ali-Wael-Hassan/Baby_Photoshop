#include "Winged_Dragon/Menu.h"
#include <string>
using namespace std;

int main(){
    cout << string(45,'=') << '\n';
    string menuName = "== Welcom to Baby Photoshop ==";
    int spaces = max(0,(int)(45 - menuName.size()) / 2);
    cout << string(spaces, ' ') << menuName << "\n";
    cout << string(45,'=') << "\n\n\n\n";
    Menu run;
    run.startMenu();
}

