#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    // Convert string to an integer;
    string pi = "314159";
    char *end;
    int pie;
    
    // strtol converts a string to an integer
    pie = strtol(pi.c_str(), &end, 10);
    
    cout << pie << endl;
    
    return 0;
}