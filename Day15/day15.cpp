#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <stack>

int hash(std::string s) {
  int current = 0;
  for(int i = 0; i < s.length(); i++) {
    current += (int)s[i];
    current *= 17;
    current %= 256;
  }
  return current;
}

struct entry {
  std::string label;
  int focal;
  bool remove;
};

int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  int res_1 = 0;
  int res_2 = 0;

  std::vector<std::string> S;

  std::vector<std::vector<struct entry>> hash_map;
  for(int i = 0; i < 256; i++) {
    std::vector<struct entry> bucket;
    hash_map.push_back(bucket);
  }

  std::vector<struct entry> L;

  if(file.is_open()) {
    std::string str;
    std::string curr;
    std::string label;
    std::string num;
    while(getline(file, str)) {
      int i = 0;
      while(i < str.length()) {
        int broke = 0;
        bool remove = false;
        while(str[i] != ',') {
          if(str[i] == '-' || str[i] == '=') {
            label = curr;
            broke = i;
            remove = str[i] == '-' ? true : false;
          }
          curr += str[i];
          i++;
        }
        int num = remove ? 0 : std::stoi(str.substr(broke + 1, i-broke));
        
        struct entry E = {label, num, remove};
        
        L.push_back(E);
        S.push_back(curr);
        curr = "";
        i++;
      }
    }
    file.close();
  };

  for(int i = 0; i < S.size(); i++) {
    res_1 += hash(S[i]);
  }

  for(int i = 0; i < L.size(); i++) {
    struct entry curr = L[i];
    int index = hash(curr.label);
    if(curr.remove) {
      for(int j = 0; j < hash_map[index].size(); j++) {
        if(hash_map[index][j].label == curr.label) {
          hash_map[index].erase(hash_map[index].begin()+j);
          break;
        }
      }
    } else {
      bool found = false;
      int found_i = 0;
      for(int j = 0; j < hash_map[index].size(); j++) {
        if(hash_map[index][j].label == curr.label) {
          found = true;
          found_i = j;
          break;
        }
      }
      if(found) {
        hash_map[index][found_i].focal = curr.focal;
      } else {
        hash_map[index].push_back(curr);
      }
    }
  }

  for(int i = 0; i < hash_map.size(); i++) {
    for(int j = 0; j < hash_map[i].size(); j++) {
      res_2 += (i+1) * (j+1) * hash_map[i][j].focal;
    }
  }

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}