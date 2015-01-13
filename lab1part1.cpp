/*
Write a program that gets file name from the command line (argv[1]) and then creates a three-column table (each a tab separated (/t) ) 

How do I use this?:
 int argv, char* argv[]
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream inf;
    string infname;
    int next, sum=0;
    
    cout << "Enter the inputfile name: ";
    cin >> infname;
    
    inf.open(infname);
    if(inf.fail()) {
        cout << "Inputfile " << infname << " failed to open.\n";
        return 1;
    }
    
    cout << "x\tx^2\tCurrent Sum\n";
    cout << "=\t===\t===========\n\n";
    while (inf >> next) {
        sum = sum + next;
        cout << next << "\t" << next*next << "\t" << sum << endl;
    }
    
    return 0;
}