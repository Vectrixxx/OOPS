// min_of_10.cpp
#include <iostream>
#include <limits>
int main() {
    int x;
    int mn = std::numeric_limits<int>::max();
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) {
        std::cin >> x;
        if (x < mn) mn = x;
    }
    std::cout << "Minimum = " << mn << std::endl;
    return 0;
}
