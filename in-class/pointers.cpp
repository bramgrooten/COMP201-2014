#include <iostream>
using namespace std;
// g++ -g pointers.cpp -o pointers.exe
// gdb pointers.exe
int main(int argc, char* argv[]) {
    // Declaring a variable allocates space in memory for that variable
    // That memory is in the stack
    int variable;
    // Declaring a pointer also declares a variable
    // That memory is also on the stack
    int* pointer;
    // Let's initialize it. This just sets the value
    variable = 500;
    // Initialize the pointer to where variable happens to be
    pointer = &variable;
    // *pointer de-references the pointer (we get what it's pointing at)
    cout << *pointer << endl;
    // So the compiler won't complain
    return 0;
}

// set breakpoints tells the debugger where to stop.
// break main // sets a breakpoint on main
// run [cmdline arguments] // run program with command line 
// step