#include <iostream>
#include <string>

int main() {

    std::string text;
    char firstLetter, isTaut;

    do {
        getline(std::cin, text);

        if(text == "*") {
            break;
        } else {

            firstLetter = tolower(text[0]);
            isTaut = 'Y';

            for(int index = 0; index < text.size(); index++) {
                if(text[index] == ' ') { 
                    if(tolower(text[index + 1]) != firstLetter) {
                        isTaut = 'N';
                    }    
                } 
            }

            std::cout << isTaut << '\n';
        }
    } while (text != "*");

    return 0;
}