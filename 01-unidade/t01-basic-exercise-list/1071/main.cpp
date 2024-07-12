#include <iostream>

void swapValue(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

int main() {

    int x, y;
    int sumOdd = 0;

    std::cin >> x >> y;

    if (x > y) {
        swapValue(x, y);
    }

    for(++x; x < y; ++x) {
        if ((x % 2) != 0) {
            sumOdd = sumOdd + x;
        }
    }

    std::cout << sumOdd << '\n';

    return 0;
}