#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main() {
    std::string password;

    while (getline(std::cin, password)) {
        bool validatedPass = true;

        if (password.size() < 6 || password.size() > 32) {
            validatedPass = false;
        } else if(std::any_of(password.begin(), password.end(), 
            [](char c){ return (static_cast<int>(c) <= 47) or (static_cast<int>(c) >= 123) or 
                               (static_cast<int>(c) >= 91 and static_cast<int>(c) <= 96) or 
                               (static_cast<int>(c) >= 58 and static_cast<int>(c) <= 64); })) {
            validatedPass = false;
        } else if (std::none_of(password.begin(), password.end(), [](char c){ return std::isdigit(c); }) ||
                   std::none_of(password.begin(), password.end(), [](char c){ return std::isupper(c); }) ||
                   std::none_of(password.begin(), password.end(), [](char c){ return std::islower(c); })) {
            validatedPass = false;
        }

        if (validatedPass) {
            std::cout << "Senha valida.\n";
        } else {
            std::cout << "Senha invalida.\n";
        }
    }
    return 0;
}
