#include <iostream>
#include <string>

int main() {
    
    int numberTest = 0, leds = 0;
    std::string number;

    std::cin >> numberTest;
    std::cin.ignore();

    for(int count = 0; count < numberTest; count++) {
        leds = 0;
        getline(std::cin, number);

        for(const char cNumb: number) {
            switch (cNumb) {
                case '1':
                    leds += 2;
                    break;
                case '2':
                    leds += 5;
                    break;
                case '3':
                    leds += 5;
                    break;
                case '4':
                    leds += 4;
                    break;
                case '5':
                    leds += 5;
                    break;
                case '6':
                    leds += 6;
                    break;
                case '7':
                    leds += 3;
                    break;
                case '8':
                    leds += 7;
                    break;
                case '9':
                    leds += 6;
                    break;
                case '0':
                    leds += 6;
                    break;
                default:
                    break;
            }
        }
        std::cout << leds << " leds\n";
    }
    return 0;
}