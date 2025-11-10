// string_reverse.cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    cout << "Enter a string (single line):\n";
    getline(cin, s);
    cout << "Reversed: ";
    for (int i = (int)s.size() - 1; i >= 0; --i) cout << s[i];
    cout << endl;
    return 0;
}
