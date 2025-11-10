// array_sum_10.cpp
#include <iostream>
int main() {
    int a[10], sum = 0;
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) { std::cin >> a[i]; sum += a[i]; }
    std::cout << "Sum = " << sum << std::endl;
    return 0;
}
