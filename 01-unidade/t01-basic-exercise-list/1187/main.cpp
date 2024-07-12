#include <iostream>
#include <iomanip>

int main() {
    char opcChar;
    double matriz[12][12];
    double sum = 0, media = 0;

    std::cin >> opcChar;

    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 12; j++) {
            std::cin >> matriz[i][j];
        }
    }

    for(int i = 0; i < 5; i++) {
        for(int j = i + 1; j <= 11 - (i + 1); j++) {
            sum += matriz[i][j];
        }
    }

    if(opcChar == 'M') {
        media = sum / 30.0;
        std::cout << std::fixed << std::setprecision(1) << media << '\n';
    } else {
        std::cout << std::fixed << std::setprecision(1) << sum << '\n';
    }

    return 0;
}