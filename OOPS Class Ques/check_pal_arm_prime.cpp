// check_pal_arm_prime.cpp
#include <iostream>
#include <cmath>

bool isPalindrome(int n) {
    int orig = n, rev = 0;
    if (n < 0) return false; // negative: not considered palindrome here
    while (n) { rev = rev * 10 + (n % 10); n /= 10; }
    return rev == orig;
}

bool isArmstrong(int n) {
    if (n < 0) return false;
    int orig = n, sum = 0, digits = 0, t = n;
    while (t) { ++digits; t /= 10; }
    t = n;
    while (t) {
        int d = t % 10;
        sum += (int)pow(d, digits);
        t /= 10;
    }
    return sum == orig;
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int r = (int)std::sqrt(n);
    for (int i = 3; i <= r; i += 2)
        if (n % i == 0) return false;
    return true;
}

int main() {
    int a[10];
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) std::cin >> a[i];
    for (int i = 0; i < 10; ++i) {
        int val = a[i];
        std::cout << val << ": ";
        if (isPalindrome(val)) std::cout << "Palindrome, ";
        else std::cout << "Not Palindrome, ";
        if (isArmstrong(val)) std::cout << "Armstrong, ";
        else std::cout << "Not Armstrong, ";
        if (isPrime(val)) std::cout << "Prime";
        else std::cout << "Not Prime";
        std::cout << std::endl;
    }
    return 0;
}
