#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<string> words;
    
    string word;
    // Slurps in words from standard input
    // Ctrl-D if you're typing stuff in
    while (cin >> word) {
        if (word == "done") {
            break;
        }
        words.push_back(word);
    }
    // Barf out words backwards
    while (words.size() > 0) {
        cout << words.back() << endl;
        words.pop_back();
    }
}