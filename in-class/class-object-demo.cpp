#include <iostream>
#include <string>
using namespace std;
class Animal {
public:
    // This is the default constructor
    Animal() {
        greeting = "meh?";
    }
    // This is the constructor
    Animal(string thing) {
        greeting = thing;
    }
    void speak() {
        cout << greeting << endl;
    }
private:
    string greeting;
};
int main() {
    // If classes are the cookie cutter, and the objects are the cookies
    // Then by analogy the cookie dough is memory
    // These animals live on the stack
    // On a stack, exiting a function cleans up the mess
    Animal lion("roar"); // this calls the default constructor
    Animal cat("wuff");
    Animal elephant("meow");
    lion.speak();
    cat.speak();
    elephant.speak();
    
    // These animals live on the heap
    // On a heap, exiting a function doesn't clean up the mess
    // Instead, we need to explicitly delete stuff
    Animal * tiger = new Animal("roar, as well!");
    Animal * liger = new Animal("LOL");
    Animal * person;

    person = new Animal("Don't eat me");
    
    // These animals are pointers
    (*tiger).speak();
    // This syntax (above) is ugly
    // This syntax is preferable
    tiger->speak();
    liger->speak();
    person->speak();
    
    // Whenever you do something new, you need to delete, as well
    delete tiger;
    delete liger;
    delete person;
    return 0;
}