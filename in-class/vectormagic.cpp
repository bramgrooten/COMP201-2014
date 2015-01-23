#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char* argv[]) {
    // vector<type> vector_name(size);
    // vector<type> vector_name;
    vector<long long> numbers(50);
    
//    cout << sizeof(long long) << endl;

    // 1 2 4 8 16 32 ...

    for(int i = 0; i < 50; i++) {
        cout << "size: " << numbers.size() << " capacity " << numbers.capacity() << endl;
        numbers.push_back(pow(2,i));
//        numbers[i] = pow(2,i);
    }
    
    for(int i = 0; i < 50; i++) {
        cout << numbers[i] << endl;
    }
    
    return 0;
}

void array_junk() {
    // Create an array of 50 numbers
    // type array_name[size]
//    long long numbers[50];
    int numbers[50] = {}; // zero-fill, ftw!
    
    // array[index] = value;

    for(int i = 0; i < 50; i++) {
        numbers[i] = 42;
    }
    
    for(int i = 0; i < 50; i++) {
        cout << numbers[i] << endl;
    }

}