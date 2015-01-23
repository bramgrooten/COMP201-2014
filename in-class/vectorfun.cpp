#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// Comment
/* Also a comment */

int main(int argc, char* argv[]) {
    vector<long long> numbers(50); // inital capacity and size
    
    // array_variable[index] = value
    // 0 2 4 8 16 32 64 ...
    for (int i = 0; i < 50; i++) {
        cout << "size: " << numbers.size() << " capacity: " << numbers.capacity() << endl;
//        numbers.push_back(pow(2, i) - 1);
        numbers[i] = pow(2, i);
    }
    
    /*
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << endl;
    }
    */
    return 0;
}

void array_version() {
    long long numbers[50];
    
    // array_variable[index] = value
    // 0 2 4 8 16 32 64 ...
    for (int i = 0; i < 50; i++) {
        numbers[i] = pow(2, i);
    }
    
    for (int i = 0; i < 50; i++) {
        cout << numbers[i] << endl;
    }
}