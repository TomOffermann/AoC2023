#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <stack>

// You need to insert two new-lines at the end in your input file

bool matches_row(int rowA, int rowB, std::vector<std::string>& map) {
  int height = map.size();
  if(rowA < 0 || rowA >= height || rowB < 0 || rowB >= height) {
    std::cout << "Something went wrong\n";
    return false;
  }
  for(int i = 0; i < map[0].length(); i++) {
    if(map[rowA][i] != map[rowB][i]) return false;
  }
  return true;
}

bool matches_col(int colA, int colB, std::vector<std::string>& map) {
  int width = map[0].length();
  if(colA < 0 || colA >= width || colB < 0 || colB >= width) {
    std::cout << "Something went wrong\n";
    return false;
  }
  for(int i = 0; i < map.size(); i++) {
    if(map[i][colA] != map[i][colB]) return false;
  }
  return true;
}

std::pair<int,int> find_sym(std::vector<std::string>& map, int l_col = 10000000, int l_row = 10000000) {
  for(int col = 0; col < map[0].length() - 1; col++) {
    if(col == l_col) {
      continue;
    }
    if(matches_col(col, col+1, map)) {
      int end = map[0].length() - 2 - col;
      int outwards = std::min(col, end);
      bool symmetric = true;
      for(int i = 1; i <= outwards; i++) {
        if(!matches_col(col-i, col+1+i, map)) {
          symmetric = false;
          break;
        }
      }
      if(symmetric) {
        std::pair<int,int> p;
        p.first = col;
        p.second = 1;
        return p;
      };
    }
  }

  for(int row = 0; row < map.size() - 1; row++) {
    if(row == l_row) {
      continue;
    }
    if(matches_row(row, row+1, map)) {
      int end = map.size() - 2 - row;
      int outwards = std::min(row, end);
      bool symmetric = true;
      for(int i = 1; i <= outwards; i++) {
        if(!matches_row(row-i, row+1+i, map)) {
          symmetric = false;
          break;
        }
      }
      if(symmetric) {
        std::pair<int,int> p;
        p.first = row;
        p.second = 0;
        return p;
      };
    }
  }
  std::pair<int,int> p;
  p.first = 69;
  p.second = 69;
  return p;
}


int main() {
  std::fstream file;
  file.open("./test.txt", std::ios::in); 

  int res_1 = 0;
  int res_2 = 0;

  std::vector<std::vector<std::string>> S;

  if(file.is_open()) {
    std::string str;
    std::vector<std::string> s;
    while(getline(file, str)) {
      if(str.length() == 0) {
        S.push_back(s);
        s.clear();
      } else {
        s.push_back(str);
      }
    }
    file.close();
  };


  for(int j = 0; j < S.size(); j++) {
    std::pair<int,int> res = find_sym(S[j]);
    if(res.second) {
      res_1 += (res.first + 1);
    } else {
      res_1 += 100 * (res.first + 1);
    }
    std::cout << j << " " << res.first << " " << res.second << "\n";
    bool found = false;
    for(int k = 0; !found && k < S[j].size(); k++) {
      for(int l = 0; !found && l < S[j][k].length(); l++) {
        char tmp = S[j][k][l];
        char new_c = tmp == '.' ? '#' : '.';
        S[j][k][l] = new_c;
        int lc = (res.second == 0) ? 10000000 : res.first;
        int lr = (res.second == 0) ? res.first : 10000000;
        std::pair<int,int> new_res = find_sym(S[j], lc, lr);
        S[j][k][l] = tmp;
        if(!((new_res.first == res.first && new_res.second == res.second) || new_res.second == 69)) {
          std::cout << j << " " << k << " " << l << "\n";
          //std::cout << new_res.first << " " << new_res.second << "\n";
          if(new_res.second) {
            res_2 += (new_res.first + 1);
          } else {
            res_2 += 100 * (new_res.first + 1);
          }
          found = true;
          break;
        }
      }
    }
  }

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}