#include <iostream>
// Global variables/constants (allocated with the program)
// Local variables/constants  (allocated on the stack)
// Dynamically allocated data (allocated by request on the heap)
using namespace std;
int main() {
    int number, product;
    cout << "Hey, how many ints do you want? ";
    cin >> number;
    product = 1;
    
    // Ask the Operating system for some memory
    int * array = new int[number];
    for (int i = 0; i < number; i++) {
        cout << "number: ";
        cin >> array[i];
    } 
    for (int i = 0; i < number; i++) {
        product *= array[i];
    }
    while (true);
    // Clean up your mess
    delete array;
    cout << product << endl;
    return 0;
}