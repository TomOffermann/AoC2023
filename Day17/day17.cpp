#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <stack>

int main() {
  std::fstream file;
  file.open("./test.txt", std::ios::in); 

  int res_1 = 0;
  int res_2 = 0;

  if(file.is_open()) {
    std::string str;
    while(getline(file, str)) {
      
    }
    file.close();
  };

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}