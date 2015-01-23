#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// g++ file-io.cpp -o file-io.exe
// file-io input.txt
int main(int argc, char* argv[]) {
    ifstream in;
    in.open(argv[1]);
    vector<string> words;
    string word;
    while (!in.eof()) {
        in >> word;
        words.push_back(word);
//        cout << word << endl;
    }
    while (words.size() > 0) {
        cout << words.back() << endl;
        words.pop_back();
    }
    in.close();
    return 0;
}

