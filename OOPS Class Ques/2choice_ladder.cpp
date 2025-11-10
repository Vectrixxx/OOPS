#include <iostream>
using namespace std;

int main() {
    int a, b, choice;
    cout << "Enter two numbers: ";
    cin >> a >> b;

    cout << "Enter choice (1 = Minimum, 2 = Maximum): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Minimum = " << ((a < b) ? a : b) << endl;
    } else if (choice == 2) {
        cout << "Maximum = " << ((a > b) ? a : b) << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
