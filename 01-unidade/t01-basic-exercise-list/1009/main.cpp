#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


int main() {

    std::string name;
    double salary, sales, endSalary;

    cout << fixed << setprecision(2);

    std::cin >> name;
    std::cin >> salary >> sales;

    endSalary = salary + (sales * (15)/100);

    std::cout << "TOTAL = R$ " << endSalary << '\n';

    return 0;
}