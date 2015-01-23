#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    string word;
    vector<string> words;
    
    while (cin >> word) {
        words.push_back(word);
    }

    while (words.size() > 0) {
        cout << words.back() << endl;
        words.pop_back();
    }

    return 0; // success! victory, etc.
}