#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

typedef long long int ll;

ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
 
ll findlcm(int arr[], int n)
{
    ll ans = arr[0];

    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /
                (gcd(arr[i], ans)));
    return ans;
}

int calc_steps(std::string& direction, std::unordered_map<std::string, std::pair<std::string, std::string>>& G) {
  int steps = 0;
  std::string curr = "AAA";
  while(true) {
    for(int i = 0; i < direction.length(); i++) {
      curr = direction[i] == 'L' ? G[curr].first : G[curr].second;
      steps++;
      if(curr == "ZZZ") {
        return steps;
      }
    }
  }
}

long calc_all_steps(std::string& direction, std::unordered_map<std::string, std::pair<std::string, std::string>>& G, std::vector<std::string>& A) {
  int lcms[A.size()]; 
  for(int i = 0; i < A.size(); i++) {
    std::string a = A[i];
    long m = 0, n = 0;
    int j = 0;
    while(true) {
      m++;
      a = direction[j] == 'L' ? G[a].first : G[a].second;
      if(a[2] == 'Z') {
        break;
      }
      j = (j+1)%direction.length();
    }
    //std::cout << m << std::endl;
    j = (j+1)%direction.length();
    while(true) {
      n++;
      a = direction[j] == 'L' ? G[a].first : G[a].second;
      //std::cout << a << std::endl;
      if(a[2] == 'Z') {
        break;
      }
      j = (j+1)%direction.length();
    }
    std::cout << "m: " << m << ", n: " << n << std::endl;
    lcms[i] = m;
  }
  return findlcm(lcms, A.size());
}


int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  int res_1 = 0;
  long res_2 = 0;

  std::string direction;
  std::unordered_map<std::string, std::pair<std::string, std::string>> G;
  std::vector<std::string> A;

  if(file.is_open()) {
    std::string str;
    int i = 0;
    while(getline(file, str)) {
      if(i == 0) {
        direction = str;
      } else if(str.length() > 5) {
        std::pair<std::string, std::string> p;
        p.first = str.substr(7,3);
        if(str.substr(0,3)[2] == 'A') {
          A.push_back(str.substr(0,3));
        }
        p.second = str.substr(12,3);
        G[str.substr(0,3)] = p;
      }
      i++;
    }
    file.close();
    //res_1 = calc_steps(direction, G);
    res_2 = calc_all_steps(direction, G, A);
  };

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}