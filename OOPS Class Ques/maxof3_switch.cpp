#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter a 3-digit number: ";
    cin >> num;

    int a = num / 100;
    int b = (num / 10) % 10;
    int c = num % 10;

    int largest = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);

    switch (largest) {
        case 0: case 1: case 2: case 3: case 4: 
        case 5: case 6: case 7: case 8: case 9:
            cout << "Largest digit is: " << largest << endl;
            break;
        default:
            cout << "Invalid input!" << endl;
    }

    return 0;
}
