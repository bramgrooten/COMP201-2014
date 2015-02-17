#include <iostream>
using namespace std;
// C++ has references, which are nicer syntax for C-style pointers
void age_a_year(int & age) {
    age++;
}
// C-style version
void age_a_year_old_C_way(int * age) {
    (*age)++;
}
int main() {
    int jack = 50;
    age_a_year(jack);
    age_a_year_old_C_way(&jack);
    cout << jack << endl;
}