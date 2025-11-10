// odd_1_20.cpp
#include <iostream>
int main() {
    for (int i = 1; i <= 20; ++i)
        if (i % 2 != 0) std::cout << i << " ";
    std::cout << std::endl;
    return 0;
}
