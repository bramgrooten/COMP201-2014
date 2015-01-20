// Given a string, print it out in reverse!
#include <iostream>

// C-style strings: char* an array of characters. terminated by a nul character \0
#include <cstring>
// C++ style strings: a nice wrapper around char*
#include <string>

using namespace std;

/*
 * argc is the number of "parameters"
 * argv is the argument vector, aka. array of strings
 */
int main(int argc, char* argv[]) {
    string cpp_string;
    const char* c_string;
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << endl;
    }
    cin >> cpp_string;
    c_string = cpp_string.c_str();
    cout << c_string << endl;
    // Print out c_string in reverse
    for (int i = strlen(c_string) - 1; i >= 0; i--) {
        cout << c_string[i];
    }
    
    return 0;
}