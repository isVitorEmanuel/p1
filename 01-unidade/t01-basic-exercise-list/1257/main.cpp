#include <iostream>
#include <string>

int main() {
    int numTests, totalElements, posChar, sum;
    std::string text;

    std::cin >> numTests;
    std::cin.ignore();

    for(int repeat = 0; repeat < numTests; repeat++) {
        sum = 0;

        std::cin >> totalElements;
        std::cin.ignore();

        for(int element = 0; element < totalElements; element++) {
            getline(std::cin, text);

            for(int index = 0; index < text.size(); index++) {
                posChar = static_cast<int>(text[index]) - 65;
                sum += posChar + element + index;
            }
        }
        std::cout << sum << '\n';
    }

    return 0;
}
