#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  int res_1 = 0;
  int res_2 = 0;

  std::vector<int> wins;
  std::vector<int> tickets;

  if(file.is_open()) {
    std::string str;
    while(getline(file, str)) {
      std::unordered_set<int> winning;
      std::vector<int> numbers;
      int i,j;
      for(j = 0; j < str.length() && str[j] != '|'; j++);
      for(i = 0;  i < 10 && str[i] != ':'; i++);
      i+=2;
      for(;i < str.length() && i < j; i += 3) {
        winning.insert(std::stoi(str.substr(i,3)));
      }
      for(i = j + 1; i < str.length(); i += 3) {
        numbers.push_back(std::stoi(str.substr(i,3)));
      }
      
      // Task 1:
      int tmp = 0;
      int matches = 0;
      for(i = 0; i < numbers.size(); i++) {
        if(winning.find(numbers[i]) != winning.end()) {
          tmp = tmp == 0 ? 1 : tmp << 1;
          matches++;
        }
      }
      wins.push_back(matches);
      res_1 += tmp;
    }
    file.close();

    // Task 2:
    for(int i = 0; i < wins.size(); i++) {
      tickets.push_back(1);
    }
    for(int i = 0; i < tickets.size(); i++) {
      int win = wins[i];
      for(int j = i + 1; j <=tickets.size() && j <= i + win; j++) {
        tickets[j] += tickets[i];
      }
      res_2 += tickets[i];
    }
  };

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}