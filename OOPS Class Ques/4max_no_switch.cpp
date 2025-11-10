#include <iostream>
using namespace std;

int main() {
    int a, b, c, d, max;
    cout << "Enter four numbers: ";
    cin >> a >> b >> c >> d;

    // Find max using conditional operators
    max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    if (d > max) max = d;

    // Use switch to identify and print
    switch(max) {
        case 0: // dummy case, won’t be used
            break;
        default:
            cout << "Maximum = " << max << endl;
    }

    return 0;
}
