#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <stack>

bool in_bounds(int w, int h, int x, int y) {
  return x >= 0 && x < w && y >= 0 && y < h;
}

int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  int res_1 = 0;
  long res_2 = 0;

  std::vector<std::string> in;
  std::unordered_set<int> empty_col;
  std::unordered_set<int> empty_row;
  std::vector<int> stars;

  if(file.is_open()) {
    std::string str;
    int j = 0;
    while(getline(file, str)) {
      in.push_back(str);
    }
    file.close();
  };

  int width = in[0].length();
  int height = in.size();

  for(int i = 0; i < height; i++) {
    bool empty = true;
    for(int j = 0; j < width; j++) {
      if(in[i][j] == '#'){
        stars.push_back(i*width +j);
        empty = false;
      };
    }
    if(empty) empty_row.insert(i);
  }

  for(int j = 0; j < width; j++) {
    bool empty = true;
    for(int i = 0; i < height; i++) {
      if(in[i][j] == '#') empty = false;
    }
    if(empty) empty_col.insert(j);
  }

  for(int i = 0; i < stars.size(); i++) {
    for(int j = i+1; j < stars.size(); j++) {
      int ax = stars[i] % width;
      int ay = stars[i] / width;
      int bx = stars[j] % width;
      int by = stars[j] / width;

      int ystart = std::min(ay,by);
      int yend = std::max(ay,by);
      int xstart = std::min(ax,bx);
      int xend = std::max(ax,bx);
      
      for(int k = ystart+1; k <= yend; k++) {
        if(empty_row.find(k) != empty_row.end()) {
          res_1 += 2;
          res_2 += 1000000;
        } else {
          res_1 += 1;
          res_2 += 1;
        }
      }
      for(int k = xstart+1; k <= xend; k++) {
        if(empty_col.find(k) != empty_col.end()) {
          res_1 += 2;
          res_2 += 1000000;
        } else {
          res_1 += 1;
          res_2 += 1;
        }
      }
    }
  }

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}