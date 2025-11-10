#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    if (num >= 1000 && num <= 9999) {
        cout << num << " is a 4-digit number." << endl;
    } else if (num < 1000) {
        cout << num << " has less than 4 digits." << endl;
    } else {
        cout << num << " has more than 4 digits." << endl;
    }

    return 0;
}
