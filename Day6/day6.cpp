#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <algorithm>

int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  long res_1 = 1;
  long res_2 = 0;

  int n = 4;
  int times[4] = {62, 64, 91, 90};
  int dist[4] = {553, 1010, 1473, 1074};

  long time_part2 = 62649190;
  long dist_part2 = 553101014731074;

  for(int i = 0; i < n; i++) {
    int t = times[i];
    int d = dist[i];
    int combs = 0;
    for(int j = 1; j < t; j++) {
      int dist = (t-j)*j;
      if(dist > d) {
        combs++;
      }
    }
    res_1 *= combs;
  }

  long combs = 0;
  for(long j = 1; j < time_part2; j++) {
    long dist = (time_part2-j)*j;
    if(dist > dist_part2) {
      combs++;
    }
  }

  res_2 = combs;

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}