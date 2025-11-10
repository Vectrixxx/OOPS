// array_check_prime.cpp
#include <iostream>
#include <cmath>

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int r = (int)std::sqrt(n);
    for (int i = 3; i <= r; i += 2) if (n % i == 0) return false;
    return true;
}

int main() {
    int a[10];
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) std::cin >> a[i];
    for (int i = 0; i < 10; ++i)
        std::cout << a[i] << (isPrime(a[i]) ? " is Prime\n" : " is not Prime\n");
    return 0;
}
