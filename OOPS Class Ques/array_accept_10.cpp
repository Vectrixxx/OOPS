// array_accept_10.cpp
#include <iostream>
int main() {
    int a[10];
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) std::cin >> a[i];
    std::cout << "You entered: ";
    for (int i = 0; i < 10; ++i) std::cout << a[i] << " ";
    std::cout << std::endl;
    return 0;
}
