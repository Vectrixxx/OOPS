// string_copy.cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string src;
    cout << "Enter a string:\n";
    getline(cin, src);
    string dest = src; // simple copy
    cout << "Source: " << src << "\nCopied into dest: " << dest << endl;

    // If you want a C-style copy into char array (handy for learning):
    char buf[100];
    int i = 0;
    for (; i < (int)src.size() && i < 99; ++i) buf[i] = src[i];
    buf[i] = '\0';
    cout << "C-style copied string: " << buf << endl;
    return 0;
}
