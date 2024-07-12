#include <iostream>
#include <cstdbool>
#include <cmath>

int main() {

    int x1, x2, y1, y2;
    bool end = true;

    do {
        std::cin >> x1 >> y1 >> x2 >> y2;

        if(x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0) {
            end = false;
        } else {
            if(x1 == x2 && y1 == y2) {
                std::cout << "0\n";
            } else if(x1 == x2 || y1 == y2 || abs(x1 - x2) == abs(y1 - y2)) {
                std::cout << "1\n";
            } else {
                std::cout << "2\n";
            }
        }
    } while (end);

    return 0;
}