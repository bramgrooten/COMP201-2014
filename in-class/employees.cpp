#include <iostream>
using namespace std;
typedef struct {
    int age;
    char *name;
} Person;
int main() {
    int number;
    Person * employees;
    cout << "How many employees do you have? ";
    cin >> number;
    
    employees = new Person[number];
    
    for (int i = 0; i < number; i++) {
        cout << "Enter the first name: ";
        cin >> employees[i].name;
        cout << "Enter the age: ";
        cin >> employees[i].age;
    }
    for (int i = 0; i < number; i++) {
        cout << employees[i].name << " is ";
        cout << employees[i].age << " years old" << endl;
    }
    delete employees;
    return 0;
}