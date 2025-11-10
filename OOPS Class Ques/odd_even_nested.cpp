#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    if (num % 2 == 0) {
        if (num == 0) {
            cout << "0 is Even" << endl;
        } else {
            cout << num << " is Even" << endl;
        }
    } else {
        cout << num << " is Odd" << endl;
    }
    return 0;
}
