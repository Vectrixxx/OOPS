// char_array_create.cpp
#include <iostream>
int main() {
    char s1[] = "Hello";
    std::cout << "Character array content: " << s1 << std::endl;
    // show individual chars
    std::cout << "Chars: ";
    for (int i = 0; s1[i] != '\0'; ++i) std::cout << s1[i] << ' ';
    std::cout << std::endl;
    return 0;
}
