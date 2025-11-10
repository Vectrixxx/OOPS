#include <iostream>
using namespace std;

int main() {
    int a, b, c, min;
    cout << "Enter three numbers: ";
    cin >> a >> b >> c;

    min = a;   // assume first is min
    if (b < min)
        min = b;
    if (c < min)
        min = c;

    cout << "Minimum = " << min << endl;
    return 0;
}
