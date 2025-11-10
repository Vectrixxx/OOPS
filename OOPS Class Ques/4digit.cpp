#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    if (num >= 1000 && num <= 9999) {
        cout << num << " is a 4-digit number." << endl;
    } else {
        cout << num << " is NOT a 4-digit number." << endl;
    }

    return 0;
}
