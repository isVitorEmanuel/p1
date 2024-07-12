#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    double a, b;

    std::cin >> a >> b;

    auto media = (a * 3.5 + b * 7.5) / 11;

    cout << fixed << setprecision(5);

    std::cout << "MEDIA = " <<  media << '\n';

    return 0;
}