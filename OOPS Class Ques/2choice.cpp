#include <iostream>
using namespace std;

int main() {
    int a, b, choice;
    cout << "Enter two numbers: ";
    cin >> a >> b;

    cout << "Enter choice (1 = Minimum, 2 = Maximum): ";
    cin >> choice;

    if (choice == 1) {
        if (a < b)
            cout << "Minimum = " << a << endl;
        else
            cout << "Minimum = " << b << endl;
    } else {
        if (a > b)
            cout << "Maximum = " << a << endl;
        else
            cout << "Maximum = " << b << endl;
    }

    return 0;
}
