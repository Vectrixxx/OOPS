// array_check_palindrome.cpp
#include <iostream>

bool isPalindrome(int n) {
    if (n < 0) return false; // treat negative as not palindrome
    int orig = n, rev = 0;
    if (n == 0) return true;
    while (n) { rev = rev * 10 + (n % 10); n /= 10; }
    return rev == orig;
}

int main() {
    int a[10];
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) std::cin >> a[i];
    for (int i = 0; i < 10; ++i)
        std::cout << a[i] << (isPalindrome(a[i]) ? " is Palindrome\n" : " is not Palindrome\n");
    return 0;
}

