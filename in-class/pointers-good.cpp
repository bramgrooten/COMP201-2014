#include <iostream>
using namespace std;
// C has pointers
// C++ has pointers, and it also has references
// These are the same (sorta)
// References are safer
// Pointers give us so much flexibility
void increment_age(int & age) {
    age++;
}
// Ugly syntax
void increment_age_the_c_way(int * age) {
    (*age)++;
}
int main() {
    // This variable, somebody, is on the stack
    int somebody = 13;
    increment_age(somebody);
    increment_age_the_c_way(&somebody);
    cout << somebody << endl;
    return 0;
}