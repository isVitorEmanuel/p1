#include <iostream>
#include <cstdlib>

int greaterNumber(int a, int b) {

    int greatNumb = (a + b + abs(a - b))/2;

    return greatNumb;
}

int main() {

    int a, b, c, greatNumb; 

    std::cin >> a >> b >> c;

    greatNumb = greaterNumber(a, b);
    greatNumb = greaterNumber(greatNumb, c);

    std::cout << greatNumb << " eh o maior\n";

    return 0;
}