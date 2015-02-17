#include <iostream>
using namespace std;
// Global variables/constants (loaded up with the program)
// Local variables/constants (placed on the stack)
// Dyanmically allocated variables (placed on the heap)
int main() {
    // Numbers, FTW
    int number, data, product;
    product = 1;
    // Array
    int * array;
    cout << "Pick a number, any number: ";
    cin >> number;
    // new to you.. heh heh
    array = new int[number];
    for (int i = 0; i < number; i++) {
        cin >> data;
        array[i] = data;
    }
    for (int i = 0; i < number; i++) {
        product *= array[i];
    }
    // Clean up our mess
    delete array;
    cout << product << endl;
    return 0;
}