#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <numeric>
#include <stack>
#include <functional>

struct RULE {
  std::function<bool(struct NODE)> validate;
  std::string vertex;
  char type;
  bool greater;
  int val;
};

struct NODE {
  int x;
  int m;
  int a;
  int s;
};

struct INTERVAL {
  long long int start;
  long long int end;
};

bool valid(struct INTERVAL A) {
  return A.start < A.end;
}

struct INTERVAL merge(struct INTERVAL A, struct INTERVAL B) {
  struct INTERVAL C = {std::max(A.start, B.start), std::min(A.end, B.end)};
  if((A.end > B.start && A.start < B.end) || (A.start < B.end && A.end > B.start)) return C;
  return {0,0};
}

struct NODE_INT {
  struct INTERVAL x;
  struct INTERVAL m;
  struct INTERVAL a;
  struct INTERVAL s;
};

long long int DEEP_DFS(std::map<std::string, std::vector<struct RULE>>& G) {
  std::vector<struct NODE_INT> intervals;

  // DFS:
  std::stack<std::pair<std::string, struct NODE_INT>> S;
  S.push({"in", {{1,4000},{1,4000},{1,4000},{1,4000}}});
  while(!S.empty()) {
    std::pair<std::string, struct NODE_INT> curr_s = S.top();
    std::string vertex = curr_s.first;
    struct NODE_INT interval = curr_s.second;
    S.pop();
    for(int i = 0; i < G[vertex].size(); i++) {
      int v = G[vertex][i].val;
      struct INTERVAL g = {v+1,4000};
      struct INTERVAL ge = {v,4000};
      struct INTERVAL l = {1, v-1};
      struct INTERVAL le = {1, v};
      struct NODE_INT copy = interval;
      switch (G[vertex][i].type) {
        case 'x':
          copy.x = G[vertex][i].greater ? merge(g, interval.x) : merge(l, interval.x);
          interval.x = G[vertex][i].greater ? merge(le, interval.x) : merge(ge, interval.x);
          if(valid(copy.x)) {
            if(G[vertex][i].vertex == "A") {
              intervals.push_back(copy);
            } else {
              S.push({G[vertex][i].vertex, copy});
            }
          }
          break;
        case 'm':
          copy.m = G[vertex][i].greater ? merge(g, interval.m) : merge(l, interval.m);
          interval.m = G[vertex][i].greater ? merge(le, interval.m) : merge(ge, interval.m);
          if(valid(copy.m)) {
            if(G[vertex][i].vertex == "A") {
              intervals.push_back(copy);
            } else {
              S.push({G[vertex][i].vertex, copy});
            }
          }
          break;
        case 'a':
          copy.a = G[vertex][i].greater ? merge(g, interval.a) : merge(l, interval.a);
          interval.a = G[vertex][i].greater ? merge(le, interval.a) : merge(ge, interval.a);
          if(valid(copy.a)) {
            if(G[vertex][i].vertex == "A") {
              intervals.push_back(copy);
            } else {
              S.push({G[vertex][i].vertex, copy});
            }
          }
          break;
        case 's':
          copy.s = G[vertex][i].greater ? merge(g, interval.s) : merge(l, interval.s);
          interval.s = G[vertex][i].greater ? merge(le, interval.s) : merge(ge, interval.s);
          if(valid(copy.s)) {
            if(G[vertex][i].vertex == "A") {
              intervals.push_back(copy);
            } else {
              S.push({G[vertex][i].vertex, copy});
            }
          }
          break;
        case '*':
          if(G[vertex][i].vertex == "A") {
            intervals.push_back(interval);
          } else {
            if(G[vertex][i].vertex != "R") S.push({G[vertex][i].vertex, interval});
          }
          break;
      }
    }
  }

  // Calculation:
  long long res = 0;
  for(int i = 0; i < intervals.size(); i++) {
    res += (intervals[i].x.end - intervals[i].x.start + 1) * 
           (intervals[i].m.end - intervals[i].m.start + 1) * 
           (intervals[i].a.end - intervals[i].a.start + 1) * 
           (intervals[i].s.end - intervals[i].s.start + 1);
  }
  return res;
}

bool DFS(std::map<std::string, std::vector<struct RULE>>& G, struct NODE node) {
  std::map<std::string, bool> visited;

  for(const auto &p : G) {
    visited[p.first] = false;
  }

  std::stack<std::string> S;
  S.push("in");
  visited["in"] = true;
  while(!S.empty()) {
    std::string curr = S.top();
    S.pop();
    for(int i = 0; i < G[curr].size(); i++) {
      if(!visited[G[curr][i].vertex] && G[curr][i].validate(node)) {
        if(G[curr][i].vertex == "A") return true;
        if(G[curr][i].vertex == "R") return false;
        S.push(G[curr][i].vertex);
        visited[G[curr][i].vertex] = true;
        break;
      }
    }
  }
  return false;
}

int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  int res_1 = 0;
  long long int res_2 = 0;

  std::map<std::string, std::vector<struct RULE>> G;
  std::vector<struct NODE> V;

  if(file.is_open()) {
    std::string str;
    bool parse_G = true;
    while(getline(file, str)) {
      int n = str.length();
      if(n == 0) {
        parse_G = false;
        continue;
      }
      if (parse_G) {
        std::string start = "";
        std::vector<struct RULE> rules;
        int i = 0;
        for(; i < n && str[i] != '{'; i++) {
          start += str[i];
        }
        i++;
        while(i < n) {
          std::string category = "";
          for(; i < n && str[i] != '}' && str[i] != '<' && str[i] != '>'; i++) {
            category += str[i];
          }
          char op = str[i];
          i++;
          if(op == '}') {
            rules.push_back({[](struct NODE node){return true;}, category, '*', false, 0});
            break;
          } else {
            std::string num = "";
            std::string vertex = "";
            for(; i < n && isdigit(str[i]); i++) {
              num += str[i];
            }
            i++;
            for(; i < n && str[i] != ',' && str[i] != '}'; i++) {
              vertex += str[i];
            }

            std::function<bool(struct NODE)> validate = [category, num, op](struct NODE node){
              bool greater = op == '>';
              int val = std::stoi(num);
              if(category == "x") {
                return greater ? node.x > val : node.x < val;
              } else if(category == "m") {
                return greater ? node.m > val : node.m < val;
              } else if(category == "a") {
                return greater ? node.a > val : node.a < val;
              } else {
                return greater ? node.s > val : node.s < val;
              } 
            };

            struct RULE r = {validate, vertex, category[0], op == '>', std::stoi(num)};
            rules.push_back(r);
          }
          i++;
        }
        G[start] = rules;
      } else {
        int i = 0;
        for(; i < n && !isdigit(str[i]); i++);
        std::string x;
        for(; i < n && isdigit(str[i]); i++) {
          x += str[i];
        }
        for(; i < n && !isdigit(str[i]); i++);
        std::string m;
        for(; i < n && isdigit(str[i]); i++) {
          m += str[i];
        }
        for(; i < n && !isdigit(str[i]); i++);
        std::string a;
        for(; i < n && isdigit(str[i]); i++) {
          a += str[i];
        }
        for(; i < n && !isdigit(str[i]); i++);
        std::string s;
        for(; i < n && isdigit(str[i]); i++) {
          s += str[i];
        }
  
        struct NODE node = {std::stoi(x), std::stoi(m), std::stoi(a), std::stoi(s)};
        V.push_back(node);
      }
    }
    file.close();
  };
  
  for(int i = 0; i < V.size(); i++) {
    if(DFS(G, V[i])) {
      res_1 += (V[i].x + V[i].m + V[i].a + V[i].s);
    }
  }

  res_2 = DEEP_DFS(G);

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}