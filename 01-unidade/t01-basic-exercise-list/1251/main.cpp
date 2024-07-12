#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string input;
  int countReader = 0;
  while (std::cin >> input) {
      
                                                                                                                          
    if(countReader > 0) {                                                                                             
      std::cout << '\n';
    }  
    
    std::vector<int> charCount(128, 0);

    for (char c : input) {
      charCount[static_cast<int>(c)]++;
    }

    std::vector<int> charIndices;

    for (int i = 0; i < 128; i++) {
      if (charCount[i] > 0) {
        charIndices.push_back(i);
      }
    }

    std::sort(charIndices.begin(), charIndices.end(),
              [&charCount](int a, int b) {
                if (charCount[a] == charCount[b]) {
                  return a > b;
                }
                return charCount[a] < charCount[b];
              });

    for (int index : charIndices) {
      std::cout << index << " " << charCount[index] << '\n';
    }
                                                                                                              
    countReader++;
  }                                                                                                                   
  return 0;                                                                                                           
}