#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    vector<int> numbers;
    string in;
 
    cout << "RPN calculator\nEnter your postfix expression and end with a space and a period ( .)\n";
    
    while (cin >> in) {
        if (in == ".") {
            break;
        }
        int a, b;
        if (in == "+") {
            if (numbers.size()<2) {
                cout << "Your postfix expression is wrong.\n";
                return 0;
            }
            a = numbers.back();
            numbers.pop_back();
            b = numbers.back();
            numbers.pop_back();
            numbers.push_back(a+b);
        }
        else if (in == "-") {
            if (numbers.size()<2) {
                cout << "Your postfix expression is wrong.\n";
                return 0;
            }
            a = numbers.back();
            numbers.pop_back();
            b = numbers.back();
            numbers.pop_back();
            numbers.push_back(b-a);
        }
        else if (in == "*") {
            if (numbers.size()<2) {
                cout << "Your postfix expression is wrong.\n";
                return 0;
            }
            a = numbers.back();
            numbers.pop_back();
            b = numbers.back();
            numbers.pop_back();
            numbers.push_back(a*b);
        }
        else if (in == "/") {
            if (numbers.size()<2) {
                cout << "Your postfix expression is wrong.\n";
                return 0;
            }
            a = numbers.back();
            numbers.pop_back();
            b = numbers.back();
            numbers.pop_back();
            numbers.push_back(b/a);
        }
        else {
            char *end;
            int num;
            num = strtol(in.c_str(), &end, 10);
            numbers.push_back(num);
        }
    }
    
    if (numbers.size() != 1) {
        cout << "Your postfix expression is wrong.\nToo many numbers left.\n";
        return 0;
    }
    else {
        cout << "Answer = " << numbers.back() << endl;
    }
    
    return 0;
}