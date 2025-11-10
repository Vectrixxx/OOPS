// array_check_armstrong.cpp
#include <iostream>
#include <cmath>

bool isArmstrong(int n) {
    if (n < 0) return false;
    int orig = n, t = n, digits = 0, sum = 0;
    if (n == 0) digits = 1;
    while (t) { ++digits; t /= 10; }
    t = n;
    while (t) {
        int d = t % 10;
        sum += (int)std::pow(d, digits);
        t /= 10;
    }
    return sum == orig;
}

int main() {
    int a[10];
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) std::cin >> a[i];
    for (int i = 0; i < 10; ++i)
        std::cout << a[i] << (isArmstrong(a[i]) ? " is Armstrong\n" : " is not Armstrong\n");
    return 0;
}
