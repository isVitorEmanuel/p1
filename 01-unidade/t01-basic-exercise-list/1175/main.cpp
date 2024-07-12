#include <iostream>

int main() {
    int vet[20];
    int aux;

    for(int index = 0; index < 20; index++){
        std::cin >> vet[index];
    }

    for(int index = 0; index < 10; index++) {
        std::swap(vet[0 + index], vet[19 - index]);
    }

    for(int index = 0; index < 20; index++){
        std::cout << "N[" << index << "] = " << vet[index] << '\n';
    }
}