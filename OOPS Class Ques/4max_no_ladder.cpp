#include <iostream>
using namespace std;

int main() {
    int a, b, c, d;
    cout << "Enter four numbers: ";
    cin >> a >> b >> c >> d;

    if (a >= b && a >= c && a >= d)
        cout << "Maximum = " << a << endl;
    else if (b >= a && b >= c && b >= d)
        cout << "Maximum = " << b << endl;
    else if (c >= a && c >= b && c >= d)
        cout << "Maximum = " << c << endl;
    else
        cout << "Maximum = " << d << endl;

    return 0;
}
