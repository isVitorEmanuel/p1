#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    float x1, x2, y1, y2;

    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;

    auto distance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

    cout << fixed << setprecision(4);
    std::cout << distance << '\n';

    return 0;
}