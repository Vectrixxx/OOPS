#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;

    switch ( (a > b) - (b > a) ) {
        case 1:
            cout << a << " is greater." << endl;
            break;
        case -1:
            cout << b << " is greater." << endl;
            break;
        case 0:
            cout << "Both numbers are equal." << endl;
            break;
    }

    return 0;
}
