#include <iostream>

int main() {

    int testCases, pa, pb;
    int years;
    float g1, g2;

    std::cin >> testCases;

    for(int repeat = 0; repeat < testCases; repeat++) {
        years = 0;
        std::cin >> pa >> pb >> g1 >> g2; 

        while(pa <= pb) {
            years++;

            pa = pa + (pa * (g1/100));
            pb = pb + (pb * (g2/100));

            if(years > 100) {
                std::cout << "Mais de 1 seculo.\n";
                break;
            }
        }

        if(years <= 100) {
            std::cout << years << " anos.\n";
        }  
    }
    return 0;
}