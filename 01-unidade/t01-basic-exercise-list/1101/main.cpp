#include <iostream>
#include <cstdbool>

void swapValue(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

int main() {

    int m, n, sum;
    do{
        sum = 0;
        std::cin >> m >> n;

        if(m <= 0 || n <= 0) {
            break;
        } else {
            if (m > n) {
                swapValue(m, n);
            }

            for(m; m <= n; m++){
                std::cout << m << ' '; 
                sum+= m;
            }

            std::cout << "Sum=" << sum << '\n'; 
        }
    } while(true);

    return 0;
}