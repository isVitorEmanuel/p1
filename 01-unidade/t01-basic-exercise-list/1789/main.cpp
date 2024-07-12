#include <iostream>

int main() {
    int numberSlug = 0, higSpeed = 0, speed = 0;


    while (std::cin >> numberSlug) {
        
        higSpeed = 0;

        for(int slug = 0; slug < numberSlug; slug++){
            std::cin >> speed;
            if(speed > higSpeed) {
                higSpeed = speed;
            }
        }
        
        if (higSpeed < 10) {
            std::cout << 1 << '\n';
        } else if (higSpeed  >= 10 and higSpeed < 20) {
            std::cout << 2 << '\n';
        } else {
            std::cout << 3 << '\n';
        }
    }
    return 0;
}