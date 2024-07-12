#include <iostream>
#include <vector>

void printVetor(std::vector<int> vector) {
    for (int index = 0; index < 3; ++index) {
        std::cout << vector[index] << '\n';
    }
}

void sortValues(std::vector<int> vector) {

    int varAux = 0;

    for (int indexi = 0; indexi < 2; ++indexi) {
        for (int Indexj = indexi + 1; Indexj < 3; ++Indexj) {
            if (vector[indexi] > vector[Indexj]) {
                varAux = vector[indexi];
                vector[indexi] = vector[Indexj];
                vector[Indexj] = varAux;
            }
        }
    }

    printVetor(vector);
}

int main() {

    std::vector<int> values(3);

    for (int index = 0; index < 3; ++index) {
        std::cin >> values[index];
    }

    sortValues(values);
    std::cout << '\n';
    printVetor(values);

    return 0;
}