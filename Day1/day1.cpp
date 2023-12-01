#include <iostream>
#include <fstream>
#include <string>

int get_elem(bool is_first_digit, bool is_first_task, std::string& str, std::vector<std::string>& digits) {
  for(int index = 0; index < str.length(); index++) {
    int i = is_first_digit ? index : (str.length()-index-1);
    if(isdigit(str[i])) {
      return str[i] - '0';
    }
    if(!is_first_task) {
      for(int j = 0; j < digits.size(); j++) {
        std::string digit = digits[j];
        int size = digit.length();
        if(str.compare(i, size, digit) == 0) {
          return j + 1;
        }
      }
    }
  }
  return 0;
}

int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  int result_1 = 0;
  int result_2 = 0;

  std::vector<std::string> digits = {
    "one", 
    "two", 
    "three", 
    "four", 
    "five", 
    "six", 
    "seven", 
    "eight", 
    "nine"
  };


  if(file.is_open()) {
    std::string str;
    while(getline(file, str)) {
      int first_1 = get_elem(true, true, str, digits);
      int second_1 = get_elem(false, true, str, digits);
      int first_2 = get_elem(true, false, str, digits);
      int second_2 = get_elem(false, false, str, digits);
      result_1 += (10 * first_1 + second_1);
      result_2 += (10 * first_2 + second_2);
    }
    file.close();
  }
  std::cout << "Task 1: " << result_1 << ", Task 2: " << result_2 << std::endl;
}