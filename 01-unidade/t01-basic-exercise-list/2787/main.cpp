#include <iostream>

int main() {
    int l, c;

    std::cin >> l >> c;

    if(l % 2 == c % 2) {
        std::cout << 1 << '\n';
    } else {
        std::cout << 0 << '\n';
    }
    return 0;
}