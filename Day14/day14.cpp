#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <stack>

bool equal(std::vector<std::string>& A, std::vector<std::string>& B) {
  for(int i = 0; i < A.size(); i++) {
    for(int j = 0; j < A[0].length(); j++) {
      if(A[i][j] != B[i][j]) return false;
    }
  }
  return true;
}

int score(std::vector<std::string>& map) {
  int a = 0;
  for(int i = 0; i < map.size(); i++) {
    for(int j = 0; j < map[0].length(); j++) {
      if(map[i][j] == 'O') {
        a += (map.size() - i);
      }
    }
  }
  return a;
}

void rotate(std::vector<std::string>& map, bool only_north = false) {
  // North:
  for(int i = 0; i < map[0].length(); i++) {
    for(int j = 0; j < map.size(); j++) {
      if(map[j][i] == 'O') {
        int k;
        bool found = false;
        for(k = j-1; k >= 0; k--) {
          if(map[k][i] == '#' || map[k][i] == 'O') {
            found = true;
            break;
          }
        }
        k++;
        if(found || k == 0) {
          map[j][i] = '.';
          map[k][i] = 'O';
        }
      }
    }
  }
  if(only_north) return;
  // West:
  for(int i = 0; i < map.size(); i++) {
    for(int j = 0; j < map[0].length(); j++) {
      if(map[i][j] == 'O') {
        int k;
        bool found = false;
        for(k = j-1; k >= 0; k--) {
          if(map[i][k] == '#' || map[i][k] == 'O') {
            found = true;
            break;
          }
        }
        k++;
        if(found || k == 0) {
          map[i][j] = '.';
          map[i][k] = 'O';
        }
      }
    }
  }
  // South:
  for(int i = 0; i < map[0].length(); i++) {
    for(int j = map.size() - 1; j >= 0; j--) {
      if(map[j][i] == 'O') {
        int k;
        bool found = false;
        for(k = j+1; k < map.size(); k++) {
          if(map[k][i] == '#' || map[k][i] == 'O') {
            found = true;
            break;
          }
        }
        k--;
        if(found || k == map.size()-1) {
          map[j][i] = '.';
          map[k][i] = 'O';
        }
      }
    }
  }
  // East:
  for(int i = 0; i < map.size(); i++) {
    for(int j = map[0].length() - 1; j >= 0; j--) {
      if(map[i][j] == 'O') {
        int k;
        bool found = false;
        for(k = j+1; k < map[0].length(); k++) {
          if(map[i][k] == '#' || map[i][k] == 'O') {
            found = true;
            break;
          }
        }
        k--;
        if(found || k == map[0].length() - 1) {
          map[i][j] = '.';
          map[i][k] = 'O';
        }
      }
    }
  }
  return;
}

int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  int res_1 = 0;
  int res_2 = 0;

  std::vector<std::string> map;

  if(file.is_open()) {
    std::string str;
    while(getline(file, str)) {
      map.push_back(str);
    }
    file.close();
  };

  std::vector<std::string> map_copy = map;
  rotate(map_copy, true);

  res_1 = score(map_copy);

  std::vector<std::vector<std::string>> last;
  last.push_back(map);

  long cycle_len = 0;
  long rest = 0;

  for(long i = 1; i <= 1000000000; i++) {
    rotate(map);

    bool found = false;
    for(int j = last.size() - 1; j >= 0; j--) {
      if(equal(map, last[j])) {
        cycle_len = i - j;
        rest = (1000000000L - j - 1) % cycle_len;
        res_2 = score(last[j + rest + 1]);
        found = true;
        break;
      }
    }

    if(found) break;

    last.push_back(map);
  }

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}