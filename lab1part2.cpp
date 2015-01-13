/*
part 2 of lab 1
 Bram Grooten
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream inf;
    ofstream outf;
    string infname, outfname;
    int next, sum=0;
    
    cout << "Enter the inputfile name: ";
    cin >> infname;
    cout << "Enter the outputfile name: ";
    cin >> outfname;
    
    inf.open(infname);
    if(inf.fail()) {
        cout << "Inputfile " << infname << " failed to open.\n";
        return 1;
    }
    outf.open(outfname);
    if(outf.fail()) {
        cout << "Outputfile " << outfname << " failed to open.\n";
        return 1;
    }
    
    outf << "x\tx^2\tCurrent Sum\n";
    outf << "=\t===\t===========\n\n";
    while (inf >> next) {
        sum = sum + next;
        outf << next << "\t" << next*next << "\t" << sum << endl;
    }
    cout << "Check your outputfile " << outfname << ".\n";
    return 0;
}