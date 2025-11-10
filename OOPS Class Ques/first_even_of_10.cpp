// tables_of_10.cpp
#include <iostream>
int main() {
    int a[10];
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) std::cin >> a[i];
    for (int i = 0; i < 10; ++i) {
        int n = a[i];
        std::cout << "Table of " << n << ":\n";
        for (int j = 1; j <= 10; ++j)
            std::cout << n << " x " << j << " = " << n * j << '\n';
        std::cout << std::endl;
    }
    return 0;
}
