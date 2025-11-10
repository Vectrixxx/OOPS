#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;

    if (a >= b) {
        if (a == b) {
            cout << "Both numbers are equal." << endl;
        } else {
            cout << a << " is greater." << endl;
        }
    } else {
        cout << b << " is greater." << endl;
    }

    return 0;
}
