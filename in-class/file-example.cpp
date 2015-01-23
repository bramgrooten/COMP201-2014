#include <fstream>
#include <iostream>

using namespace std;

// g++ file-example.cpp -o file-reader.exe
// ./file-reader.exe input.txt
// argv[0] /path/to/the/program
// argv[1] "first" parameter passed to the program.


// argc : count of arguments
// argv : argument vector (not a real c++ vector)
int main(int argc, char* argv[]) {
    ifstream input;
    input.open(argv[1]);
    
    if (input.fail()) {
        cout << "Hey! pass a file in!" << endl;
        return 1; // sad face :-(
    }
    
    int val;
    while (input >> val) {
        cout << val << endl;
    }
    input.close();
    return 0; // success! victory, etc.
}