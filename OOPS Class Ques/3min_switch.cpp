#include <iostream>
using namespace std;

int main() {
    int a, b, c, min;
    cout << "Enter three numbers: ";
    cin >> a >> b >> c;

    // Find minimum
    min = a;
    if (b < min) min = b;
    if (c < min) min = c;

    // Use switch to display (trick)
    switch(min) {
        default:
            cout << "Minimum = " << min << endl;
    }

    return 0;
}
