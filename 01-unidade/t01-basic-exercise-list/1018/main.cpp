#include <iostream>
#include <vector>

int main() {

    int value, numberBills;
    std::vector<int> bills{100, 50, 20, 10, 5, 2, 1};

    std::cin >> value;
    std::cout << value << '\n';
    
    for(int index = 0; index < bills.size(); index++) { 
        numberBills = value / bills[index];
        std::cout << numberBills << " nota(s) de R$ " << bills[index] << ",00\n";

        value = value % bills[index];
    }   

    return 0;
}