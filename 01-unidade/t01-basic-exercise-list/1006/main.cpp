#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    double a, b, c;

    std::cin >> a >> b >> c;

    auto media = (2 * a + 3 * b + 5 * c) / 10;

    cout << fixed << setprecision(1);
    std::cout << "MEDIA = " << media << '\n'; 

    return 0;
}