#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<string> words;
    string word;
    // Read in words until we're done
    while (cin >> word) {
        if (word == "done") {
            break;
        }
        words.push_back(word);
    }
    // Barf out words in reverse
    while (words.size() > 0) {
        cout << words.back() << endl;
        words.pop_back();
    }
    return 0;
}