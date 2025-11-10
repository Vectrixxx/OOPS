#include <iostream>
using namespace std;

int main() {
    int a, b, c, d;
    cout << "Enter four numbers: ";
    cin >> a >> b >> c >> d;

    if (a > b) {
        if (a > c) {
            if (a > d)
                cout << "Maximum = " << a << endl;
            else
                cout << "Maximum = " << d << endl;
        } else {
            if (c > d)
                cout << "Maximum = " << c << endl;
            else
                cout << "Maximum = " << d << endl;
        }
    } else {
        if (b > c) {
            if (b > d)
                cout << "Maximum = " << b << endl;
            else
                cout << "Maximum = " << d << endl;
        } else {
            if (c > d)
                cout << "Maximum = " << c << endl;
            else
                cout << "Maximum = " << d << endl;
        }
    }

    return 0;
}
