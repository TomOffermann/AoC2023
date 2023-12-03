#include <iostream>
#include <fstream>
#include <string>

bool inBounds(std::vector<std::vector<bool>>& map, int x, int y) {
  return (x >= 0 && x < map.size()) && (y >= 0 && y < map[0].size());
}

bool isPartNumber(std::vector<std::vector<bool>>& map, int i, int start, int end) {
  // left side:
  int y = start - 1;
  if(inBounds(map, i , y) && map[i][y] == 1) return true;
  if(inBounds(map, i-1 , y) && map[i-1][y] == 1) return true;
  if(inBounds(map, i+1 , y) && map[i+1][y] == 1) return true;

  // top & bottom:
  for(int l = start; l <= end; l++) {
    if(inBounds(map, i-1, l) && map[i-1][l] == 1) return true;
    if(inBounds(map, i+1, l) && map[i+1][l] == 1) return true;
  }

  // right side:
  y = end;
  if(inBounds(map, i , y) && map[i][y] == 1) return true;
  if(inBounds(map, i-1 , y) && map[i-1][y] == 1) return true;
  if(inBounds(map, i+1 , y) && map[i+1][y] == 1) return true;

  return false;
}

bool connected(std::vector<int> partNum, int x, int y) {
  if(std::abs(partNum[0] - x) <= 1) {
    if(y-1 >= partNum[1] && y-1 < partNum[2]) return true;
    if(y >= partNum[1] && y < partNum[2]) return true;
    if(y+1 >= partNum[1] && y+1 < partNum[2]) return true;
  }
  return false;
}

int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  int res_1 = 0;
  int res_2 = 0;

  std::vector<std::vector<bool>> map;
  std::vector<std::string> mapC;

  std::vector<std::vector<int>> gears;
  std::vector<std::vector<int>> partNums;

  if(file.is_open()) {
    std::string str;
    while(getline(file, str)) {
      std::vector<bool> line;
      for(int i = 0; i < str.length(); i++) {
        std::vector<int> gear;
        line.push_back(str[i] == '.' ? 0 : 1);
        if(str[i] == '*') {
          // gear = [x, y]
          gear.push_back(map.size());
          gear.push_back(i);
          gears.push_back(gear);
        }
      }
      map.push_back(line);
      mapC.push_back(str);
    }
    file.close();
  };

  for(int i = 0; i < map.size(); i++) {
    for(int j = 0; j < map[i].size(); j++) {
      if(isdigit(mapC[i][j])) {
        int start = j;
        int end;
        for(end = j+1; end < map[i].size() && isdigit(mapC[i][end]); end++);
        if(isPartNumber(map, i, start, end)) {
          int n = stoi(mapC[i].substr(start, end-start));
          res_1 += n;
          std::vector<int> partNum;

          // partNum = [i, start, end, number]
          partNum.push_back(i);
          partNum.push_back(start);
          partNum.push_back(end);
          partNum.push_back(n);

          partNums.push_back(partNum);
        }
        j = end;
      }
    }
  };
  
  for(int i = 0; i < gears.size(); i++) {
    std::vector<int> connectedNums;
    for(int j = 0; j < partNums.size(); j++) {
      if(connected(partNums[j], gears[i][0], gears[i][1])) {
        connectedNums.push_back(partNums[j][3]);
      }
    }
    if(connectedNums.size() == 2) {
      res_2 += (connectedNums[0] * connectedNums[1]);
    }
  }

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}