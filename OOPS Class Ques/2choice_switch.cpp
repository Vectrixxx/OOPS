#include <iostream>
using namespace std;

int main() {
    int a, b, choice;
    cout << "Enter two numbers: ";
    cin >> a >> b;

    cout << "Enter choice (1 = Minimum, 2 = Maximum): ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Minimum = " << ((a < b) ? a : b) << endl;
            break;
        case 2:
            cout << "Maximum = " << ((a > b) ? a : b) << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
