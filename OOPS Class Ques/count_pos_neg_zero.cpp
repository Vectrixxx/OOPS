// count_pos_neg_zero.cpp
#include <iostream>
int main() {
    int x, pos=0, neg=0, zer=0;
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) {
        std::cin >> x;
        if (x > 0) ++pos;
        else if (x < 0) ++neg;
        else ++zer;
    }
    std::cout << "Positive: " << pos << "\nNegative: " << neg << "\nZero: " << zer << std::endl;
    return 0;
}
