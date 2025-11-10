// factorials_of_10.cpp
#include <iostream>

long long factorial(int n) {
    if (n < 0) return -1; // indicate undefined for negative
    long long f = 1;
    for (int i = 2; i <= n; ++i) f *= i;
    return f;
}

int main() {
    int a[10];
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) std::cin >> a[i];
    for (int i = 0; i < 10; ++i) {
        int n = a[i];
        long long f = factorial(n);
        if (f < 0) std::cout << n << ": Factorial undefined for negative numbers.\n";
        else std::cout << n << "! = " << f << std::endl;
    }
    return 0;
}
