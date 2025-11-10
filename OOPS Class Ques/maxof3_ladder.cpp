#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter a 3-digit number: ";
    cin >> num;

    int a = num / 100;
    int b = (num / 10) % 10;
    int c = num % 10;

    if (a >= b && a >= c)
        cout << "Largest digit is: " << a << endl;
    else if (b >= a && b >= c)
        cout << "Largest digit is: " << b << endl;
    else
        cout << "Largest digit is: " << c << endl;

    return 0;
}
