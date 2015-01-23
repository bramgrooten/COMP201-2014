#include <string>
#include <iostream>

using namespace std;

int main() {
    string something;
    
    cin >> something;
    
    if (something == "42") {
        cout << "really? that's crazy!" << endl;
    }
    
    cout << something;
}