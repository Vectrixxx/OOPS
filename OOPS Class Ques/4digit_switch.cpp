#include <iostream>
using namespace std;

int main() {
    int num, count = 0, temp;
    cout << "Enter a number: ";
    cin >> num;

    temp = num;
    while (temp != 0) {
        temp /= 10;
        count++;
    }

    switch (count) {
        case 4:
            cout << num << " is a 4-digit number." << endl;
            break;
        default:
            cout << num << " is NOT a 4-digit number." << endl;
    }

    return 0;
}
