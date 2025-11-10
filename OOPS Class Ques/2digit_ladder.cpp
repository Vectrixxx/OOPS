#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    if (num >= 10 && num <= 99) {
        cout << num << " is a 2-digit positive number." << endl;
    } else if (num <= -10 && num >= -99) {
        cout << num << " is a 2-digit negative number." << endl;
    } else {
        cout << num << " is NOT a 2-digit number." << endl;
    }

    return 0;
}
