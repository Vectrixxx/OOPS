#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    cout << "Enter three numbers: ";
    cin >> a >> b >> c;

    if (a < b) {
        if (a < c)
            cout << "Minimum = " << a << endl;
        else
            cout << "Minimum = " << c << endl;
    } else {
        if (b < c)
            cout << "Minimum = " << b << endl;
        else
            cout << "Minimum = " << c << endl;
    }

    return 0;
}
