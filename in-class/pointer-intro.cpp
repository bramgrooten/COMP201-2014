#include <iostream>

using namespace std;

// g++ -g pointer-intro.cpp -o pointers.exe
// gdb pointers.exe

int main(int argc, char *argv[]) {
    // Declaring a variable allocates space for it in RAM
    int data = 70;         
    // The address of the data is the location in RAM
    // (Read &data as address of data)
    int *pointer = &data;
    // *pointer read as: de-reference pointer (get to what it's pointing at)
    cout << *pointer << endl;
    // Print out command line arguments
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << endl;
    }
    return 0;
}

// break main // sets a breakpoint on main (tell it where to stop)
// run [arguments] // run program with arguments
// print variable  // print variable
// print &variable // print out where in memory the variable is
// print *pointer  // print the dereference pointer
