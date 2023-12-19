#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <numeric>
#include <stack>
#include <queue>

bool in_bounds(int x, int y, int W, int H) {
  return x >= 0 && x < W && y >= 0 && y < H;
}

enum DIR {LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3};

struct edge {
  int weight;
  int vertex;
  DIR dir;
};

int dijkstra(int W, int H, std::vector<std::string>& map, int min, int max) {
  std::priority_queue<std::tuple<int,int,int,int>, std::vector<std::tuple<int,int,int,int>>, std::greater<std::tuple<int,int,int,int>>> pq;
  
  bool visited[W * H][4][max+2];
  for(int i = 0; i < W * H; i++) {
    for(int j = 0; j < 4; j++) {
      for(int k = 0; k <= max + 1; k++) {
        visited[i][j][k] = false;
      }
    }
  }
 
  std::vector<int> dist(W * H, 999999);
 
  pq.push({0, 0, RIGHT, 1}); // cost, vertex, direction, on_straight
  pq.push({0, 0, DOWN, 1});  // cost, vertex, direction, on_straight

  while (!pq.empty()) {
      int cost_u = std::get<0>(pq.top());
      int u = std::get<1>(pq.top());
      DIR dir_u = (DIR) std::get<2>(pq.top());
      int on_straight_u = std::get<3>(pq.top());
      pq.pop();

      dist[u] = std::min(dist[u], cost_u);

      if(visited[u][dir_u][on_straight_u]){
        continue;
      } else {
        visited[u][dir_u][on_straight_u] = true;
      }

      int x = u % W;
      int y = u / W;

      int new_x = dir_u == LEFT ? x-1 : (dir_u == RIGHT ? x+1 : x);
      int new_y = dir_u == UP ? y-1 : (dir_u == DOWN ? y+1 : y);

      if(!in_bounds(new_x,new_y,W,H)) continue;

      int new_cost = cost_u + (map[new_y][new_x] - '0');

      std::vector<DIR> S;
      if(on_straight_u >= min && on_straight_u <= max) {
        if(new_x == W-1 && new_y == H-1) return new_cost;
      }
      if(dir_u == LEFT) {
        S.push_back(LEFT);
        S.push_back(UP);
        S.push_back(DOWN);
      } else if(dir_u == DOWN) {
        S.push_back(LEFT);
        S.push_back(RIGHT);
        S.push_back(DOWN);
      } else if(dir_u == RIGHT) {
        S.push_back(RIGHT);
        S.push_back(UP);
        S.push_back(DOWN);
      } else {
        S.push_back(LEFT);
        S.push_back(RIGHT);
        S.push_back(UP);
      }
      for(int i = 0; i < S.size(); i++) {
        int new_on_straight = dir_u == S[i] ? on_straight_u + 1 : 1;
        if((dir_u != S[i] && on_straight_u < min) || new_on_straight > max) continue;
        pq.push(std::make_tuple(new_cost, new_y * W + new_x, S[i], new_on_straight));
      }
  }
  return -1;
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

  int W = map[0].length() ;
  int H = map.size();

  res_1 = dijkstra(W, H, map, 1, 3);
  res_2 = dijkstra(W, H, map, 4, 10);

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}