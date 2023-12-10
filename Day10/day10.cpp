#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <stack>

bool in_bounds(std::vector<std::vector<int>>& G, int pos) {
  return pos >= 0 && pos < G.size();
}

struct node {
  char type;
  int v;
  int time;
};

int main() {
  std::fstream file;
  file.open("./thorge.txt", std::ios::in); 

  int res_1 = 0;
  int res_2 = 0;

  std::vector<std::vector<int>> G;
  std::string map;

  int width = 0;
  int height = 0;
  int S = 0;

  if(file.is_open()) {
    std::string str;
    int y = 0;
    int n = 0;
    while(getline(file, str)) {
      map += str;
      int l = str.size();
      width = l;
      for(int x = 0; x < l; x++) {
        char c = str[x];
        std::vector<int> N;
        if(c!='.') {
          if(c == 'S') {
            S = l * y + x;
            N.push_back(l * y + x + 1);
          } else {
            switch (c) {
              case 'F':
                N.push_back(l * y + x + 1);
                N.push_back(l * (y+1) + x);
                break;
              case 'L':
                N.push_back(l * y + x + 1);
                N.push_back(l * (y-1) + x);
                break;
              case '|':
                N.push_back(l * (y+1) + x);
                N.push_back(l * (y-1) + x);
                break;
              case '-':
                N.push_back(l * y + x + 1);
                N.push_back(l * y + x - 1);
                break;
              case 'J':
                N.push_back(l * (y-1) + x);
                N.push_back(l * y + x - 1);
                break;
              case '7':
                N.push_back(l * (y+1) + x);
                N.push_back(l * y + x - 1);
                break;
            }
          }
        }
        G.push_back(N);
      }
      y++;
    }
    height = y;
    file.close();
  };

  bool visited[G.size()];
  int distances[G.size()];
  for(int i = 0; i < G.size(); i++){
    visited[i] = false;
    distances[i] = 0;
  }

  bool found = false;
  int distance = 0;
  std::stack<int> stack;
  std::stack<int> dist;
  stack.push(S);
  dist.push(0);
  visited[S] = true;
  while(!stack.empty() && !found) {
    int curr = stack.top();
    int curr_dist = dist.top();
    distances[curr] = curr_dist;
    stack.pop();
    dist.pop();
    for(int i = 0; i < G[curr].size(); i++) {
      if(G[curr][i] == S && curr_dist > 1) {
        found = true;
        distance = curr_dist + 1;
        break;
      }
      if(in_bounds(G,G[curr][i]) && !visited[G[curr][i]]) {
        visited[G[curr][i]] = true;
        stack.push(G[curr][i]);
        dist.push(curr_dist+1);
      }
    }
  }

  res_1 =  (distance+1) / 2;

  res_2 = 0;
  // 413 - 455
  for(int y = 0; y < height; y++) {
    bool inside = false;
    for(int x = 0; x < width; x++) {
      int v = y * width + x;
      if(!visited[v] && inside) {
        res_2++;
      }
      if(visited[v] && map[v] == '|') {
        inside = !inside;
      }
      if(visited[v] && map[v] != '|') {
        char start_line = map[v];
        if(!(start_line == 'F' || start_line == 'L')) {
          std::cout << "Something went wrong! \n";
        }
        for(int i = x+1; i < width; i++) {
          if(map[y*width + i] != '-') {
            if(map[y*width + i] == '7') {
              if(start_line != 'F') {
                inside = !inside;
              }
            } else {
              if(start_line == 'F') {
                inside = !inside;
              }
            }
            x = i;
            break;
          }
        }
      }
    }
  }



  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}