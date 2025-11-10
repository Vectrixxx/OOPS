// count_two_digit.cpp
#include <iostream>
#include <cmath>
int main() {
    int a[10], cnt = 0;
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) {
        std::cin >> a[i];
        int x = std::abs(a[i]);
        if (x >= 10 && x <= 99) ++cnt;
    }
    std::cout << "Two-digit numbers count = " << cnt << std::endl;
    return 0;
}
