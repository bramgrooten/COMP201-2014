/*
Write a small program that counts from 1 to 100. However, if the number is 
divisible by 3, instead print "Fizz". If the number is divisible by 5, print
"Buzz" instead. If the number is divisible by both 3 and 5, print "FizzBuzz".
*/

// Don't have an IDE? Try http://ideone.com (select C++14 from the langugae list)
#include <iostream>

using namespace std;

int main() {
    for (int i = 1; i <= 100; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            cout << "FizzBuzz" << endl;
        } else if (i % 3 == 0) {
            cout << "Fizz" << endl;
        } else if (i % 5 == 0) {
            cout << "Buzz" << endl;
        } else {
            cout << i << endl;
        }
    }
    return 0;
}