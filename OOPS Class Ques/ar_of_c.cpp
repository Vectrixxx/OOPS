#include <iostream>
using namespace std;

int main() {
    float radius, area;
    const float PI = 3.14159; // constant value of pi

    // Input radius
    cout << "Enter the radius of the circle: ";
    cin >> radius;

    // Calculate area
    area = PI * radius * radius;

    // Output result
    cout << "Area of Circle = " << area << endl;

    return 0;
}
