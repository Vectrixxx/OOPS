#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    cout << "Enter three numbers: ";
    cin >> a >> b >> c;

    if (a <= b && a <= c)
        cout << "Minimum = " << a << endl;
    else if (b <= a && b <= c)
        cout << "Minimum = " << b << endl;
    else
        cout << "Minimum = " << c << endl;

    return 0;
}
