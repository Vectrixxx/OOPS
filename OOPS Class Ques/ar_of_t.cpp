#include <iostream>
using namespace std;

int main() {
    float base, height, area;

    // Input base and height
    cout << "Enter the base of the triangle: ";
    cin >> base;

    cout << "Enter the height of the triangle: ";
    cin >> height;

    // Calculate area
    area = 0.5 * base * height;

    // Output result
    cout << "Area of Triangle = " << area << endl;

    return 0;
}
