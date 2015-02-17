#include <iostream>
using namespace std;
int main() {
    char * array = new char[26];
    for (int i = 0; i < 26; i++) {
        array[i] = 'A' + i;
    }
    for (int i = 0; i < 26; i++) {
        // The next line of code:
        cout << array[i];
        // is the same as the line below:
        cout << *(array + i);
    }
}