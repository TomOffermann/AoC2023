#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <stack>

enum DIR {LEFT = 0, RIGHT = 1, TOP = 2, BOTTOM = 3};

bool in_bounds(int x, int y, int width, int height) {
  return x >= 0 && x < width && y >= 0 && y < height;
}

struct node {
  DIR dir;
  char type;
  int x;
  int y;
};

struct node get_n(std::vector<struct node>& V, int x, int y, DIR d, int W) {
  // (1,2,3,4) * x * y
  // i = 0, ..., w-1 => i*4
  int i = 4 * y * W + 4 * x;
  switch (d) {
    case LEFT:
      return V[i];
      break;
    case BOTTOM:
      return V[i+1];
      break;
    case RIGHT:
      return V[i+2];
      break;
    case TOP:
      return V[i+3];
      break;
  }
}

void print(struct node v) {
  std::cout << "[" << v.type << "], " << ((v.dir == LEFT) ? "LEFT" : (v.dir == BOTTOM ? "BOTTOM" : (v.dir == RIGHT ? "RIGHT" : "UP"))) << ", [" << v.x << "," << v.y << "]" << std::endl;
}

int DFS(std::unordered_map<int, std::vector<struct node>>& G, std::vector<struct node>& V, struct node start, int W, int H) {
  int res = 0;
  bool visited[V.size()];
  for(int i = 0; i < V.size(); i++) {
    visited[i] = false;
  }

  std::stack<struct node> stack;
  stack.push(start);
  visited[4 * start.y * W + 4 * start.x + start.dir] = true;
  while(!stack.empty()) {
    struct node curr = stack.top();
    int index_curr = 4 * curr.y * W + 4 * curr.x + curr.dir;
    stack.pop();
    for(int i = 0; i < G[index_curr].size(); i++) {
      struct node u = G[index_curr][i];
      int index_u = 4 * u.y * W + 4 * u.x + u.dir;
      if(!visited[index_u]) {
        visited[index_u] = true;
        stack.push(u);
      }
    }
  }

  for(int i = 0; i < W; i++) {
    for(int j = 0; j < H; j++) {
      int s = j * 4 * W + i * 4;
      if(visited[s] || visited[s+1] || visited[s+2] || visited[s+3]) {
        res++;
      }
    }
  }

  return res;
}

int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  int res_1 = 0;
  int res_2 = 0;

  std::unordered_map<int, std::vector<struct node>> G;
  std::vector<struct node> V;

  int W,H;

  if(file.is_open()) {
    std::string str;
    int y = 0;
    while(getline(file, str)) {
      W = str.length();
      for(int i = 0; i < W; i++) {
        struct node u,v,w,x;
        u = {LEFT,   str[i], i, y};
        v = {BOTTOM, str[i], i, y};
        w = {RIGHT,  str[i], i, y};
        x = {TOP,    str[i], i, y};
        V.push_back(u);
        V.push_back(v);
        V.push_back(w);
        V.push_back(x);
      }
      y++;
      H = y;
    }
    file.close();
  };

  for(int i = 0; i < V.size(); i++) {
    struct node v = V[i];
    std::vector<struct node> N;
    switch (v.type) {
      case '/':
        if(v.dir == LEFT) {
          if(in_bounds(v.x, v.y-1, W, H)) N.push_back(get_n(V,v.x,v.y-1,BOTTOM,W));
        } else if(v.dir == BOTTOM) {
          if(in_bounds(v.x+1, v.y, W, H)) N.push_back(get_n(V,v.x+1,v.y,LEFT,W));
        } else if(v.dir == RIGHT) {
          if(in_bounds(v.x, v.y+1, W, H)) N.push_back(get_n(V,v.x,v.y+1,TOP,W));
        } else {
          if(in_bounds(v.x-1, v.y, W, H)) N.push_back(get_n(V,v.x-1,v.y,RIGHT,W));
        }
        break;
      case '\\':
        if(v.dir == LEFT) {
          if(in_bounds(v.x, v.y+1, W, H)) N.push_back(get_n(V,v.x,v.y+1,TOP,W));
        } else if(v.dir == BOTTOM) {
          if(in_bounds(v.x-1, v.y, W, H)) N.push_back(get_n(V,v.x-1,v.y,RIGHT,W));
        } else if(v.dir == RIGHT) {
          if(in_bounds(v.x, v.y-1, W, H)) N.push_back(get_n(V,v.x,v.y-1,BOTTOM,W));
        } else {
          if(in_bounds(v.x+1, v.y, W, H)) N.push_back(get_n(V,v.x+1,v.y,LEFT,W));
        }
        break;
      case '-':
        if(v.dir == LEFT) {
          if(in_bounds(v.x+1, v.y, W, H)) N.push_back(get_n(V,v.x+1,v.y,LEFT,W));
        } else if(v.dir == BOTTOM) {
          if(in_bounds(v.x+1, v.y, W, H)) N.push_back(get_n(V,v.x+1,v.y,LEFT,W));
          if(in_bounds(v.x-1, v.y, W, H)) N.push_back(get_n(V,v.x-1,v.y,RIGHT,W));
        } else if(v.dir == RIGHT) {
          if(in_bounds(v.x-1, v.y, W, H)) N.push_back(get_n(V,v.x-1,v.y,RIGHT,W));
        } else {
          if(in_bounds(v.x+1, v.y, W, H)) N.push_back(get_n(V,v.x+1,v.y,LEFT,W));
          if(in_bounds(v.x-1, v.y, W, H)) N.push_back(get_n(V,v.x-1,v.y,RIGHT,W));
        }
        break;
      case '|':
        if(v.dir == LEFT) {
          if(in_bounds(v.x, v.y+1, W, H)) N.push_back(get_n(V,v.x,v.y+1,TOP,W));
          if(in_bounds(v.x, v.y-1, W, H)) N.push_back(get_n(V,v.x,v.y-1,BOTTOM,W));
        } else if(v.dir == BOTTOM) {
          if(in_bounds(v.x, v.y-1, W, H)) N.push_back(get_n(V,v.x,v.y-1,BOTTOM,W));
        } else if(v.dir == RIGHT) {
          if(in_bounds(v.x, v.y+1, W, H)) N.push_back(get_n(V,v.x,v.y+1,TOP,W));
          if(in_bounds(v.x, v.y-1, W, H)) N.push_back(get_n(V,v.x,v.y-1,BOTTOM,W));
        } else {
          if(in_bounds(v.x, v.y+1, W, H)) N.push_back(get_n(V,v.x,v.y+1,TOP,W));
        }
        break;
      default:
        if(v.dir == LEFT) {
          if(in_bounds(v.x+1, v.y, W, H)) N.push_back(get_n(V,v.x+1,v.y,LEFT,W));
        } else if(v.dir == BOTTOM) {
          if(in_bounds(v.x, v.y-1, W, H)) N.push_back(get_n(V,v.x,v.y-1,BOTTOM,W));
        } else if(v.dir == RIGHT) {
          if(in_bounds(v.x-1, v.y, W, H)) N.push_back(get_n(V,v.x-1,v.y,RIGHT,W));
        } else {
          if(in_bounds(v.x, v.y+1, W, H)) N.push_back(get_n(V,v.x,v.y+1,TOP,W));
        }
        break;
    }
    G[4 * v.y * W + 4 * v.x + v.dir] = N;
  }

  struct node start = V[0];
  res_1 = DFS(G,V,start,W,H);

  for(int i = 0; i < W; i++) {
    struct node s_top = V[4*i + 3];
    struct node s_bottom = V[4 * (H-1) * W + 4*i + 1];
    res_2 = std::max(res_2, DFS(G,V,s_top,W,H));
    res_2 = std::max(res_2, DFS(G,V,s_bottom,W,H));
  }

  for(int i = 0; i < H; i++) {
    struct node s_left = V[4*i*W];
    struct node s_right = V[4*i*W + 4*(W-1) + 2];
    res_2 = std::max(res_2, DFS(G,V,s_left,W,H));
    res_2 = std::max(res_2, DFS(G,V,s_right,W,H));
  }

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}