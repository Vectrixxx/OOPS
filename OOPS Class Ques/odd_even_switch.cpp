#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    switch (num % 2) {
        case 0:
            cout << num << " is Even" << endl;
            break;
        case 1:
        case -1: // handle negative odd numbers
            cout << num << " is Odd" << endl;
            break;
        default:
            cout << "Unexpected case" << endl;
    }
    return 0;
}
