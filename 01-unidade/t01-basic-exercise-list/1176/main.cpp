#include <iostream>

int main() {

    int numTest, position = 0;
    long long int vetFib[61] = {0};

    vetFib[0] = 0;
    vetFib[1] = 1;

    for(int index = 2; index < 61; index++) {
        vetFib[index] = vetFib[index - 1] + vetFib[index - 2];
    }

    std::cin >> numTest; 

    for(int repeat = 0; repeat < numTest; repeat++) {
        std::cin >> position;

        std::cout << "Fib(" << position << ") = " << vetFib[position] << '\n';
    }
    return 0;
}