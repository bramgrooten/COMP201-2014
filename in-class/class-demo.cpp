#include <iostream>
using namespace std;

class Object {
public:
    // Constructor
    Object(string saythis) {
        greeting = saythis;
    }
    void speak() {
        cout << greeting << endl;
    }
private:
    string greeting;
};

int main() {
    // Stack allocation
    Object cow("moo");
    Object pig("oink");
    
    // Heap allocation
    Object * person;
    person = new Object("hello");
    
    cow.speak();
    pig.speak();
    
    // This is dorky:
    (*person).speak();
    // is the same as
    // Please do it this way:
    person->speak();
    
    delete person;
}