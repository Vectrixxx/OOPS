#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter a 3-digit number: ";
    cin >> num;

    int a = num / 100;        // first digit
    int b = (num / 10) % 10;  // second digit
    int c = num % 10;         // third digit

    int largest = a;

    if (b > largest)
        largest = b;
    if (c > largest)
        largest = c;

    cout << "Largest digit is: " << largest << endl;

    return 0;
}
