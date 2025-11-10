#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    int digits = 0, temp = num;

    if (temp < 0) temp = -temp; // handle negative numbers

    while (temp > 0) {
        temp /= 10;
        digits++;
    }

    switch (digits) {
        case 2:
            cout << num << " is a 2-digit number." << endl;
            break;
        default:
            cout << num << " is NOT a 2-digit number." << endl;
    }

    return 0;
}
