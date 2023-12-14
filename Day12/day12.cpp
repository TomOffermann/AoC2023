#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <stack>

int num_digits(long x)  
{  
    int offset = x < 0 ? 1 : 0;
    x = abs(x);
    return offset + (x < 10 ? 1 :   
        (x < 100 ? 2 :   
        (x < 1000 ? 3 :   
        (x < 10000 ? 4 :   
        (x < 100000 ? 5 :   
        (x < 1000000 ? 6 :   
        (x < 10000000 ? 7 :  
        (x < 100000000 ? 8 :  
        (x < 1000000000 ? 9 :  
        (x < 10000000000 ? 10 : 
        (x < 100000000000 ? 11 :
        (x < 1000000000000 ? 12 : 
        (x < 10000000000000 ? 13 :
        (x < 100000000000000 ? 14 : 15))))))))))))));  
}  

std::vector<std::vector<std::vector<long long int>>> create_memo(int n, int t, int s) {
  std::vector<std::vector<std::vector<long long int>>> memo;
  for(int i = 0; i < n; i++) {
    std::vector<std::vector<long long int>> outer;
    for(int j = 0; j <= t; j++) {
      std::vector<long long int> inner;
      for(int k = 0; k < s; k++) {
        inner.push_back(-1);
      }
      outer.push_back(inner);
    }
    memo.push_back(outer);
  }
  return memo;
};

long long int dp_fits(std::string& s, std::vector<int>& nums, int i, int j, int k, std::vector<std::vector<std::vector<long long int>>>& memo) {
  if(i == 0) {
    if(s[0] == '#') {
      if(j == 0 && k == nums[0] - 1) {
        return 1;
      } else {
        return 0;
      }
    } else if(s[0] == '?') {
      if((j+1 == 0 && k == 0) || (j == 0 && k == nums[0]) || (j == 0 && k == nums[0]-1)) {
        return 1;
      } else {
        return 0;
      }
    } else {
      if((j+1 == 0 && k == 0) || (j == 0 && k == nums[0])) {
        return 1;
      } else {
        return 0;
      }
    }
  } else {
    if(i < 0 || j+1 < 0 || k >= s.length()) return 0;
    if(memo[i][j+1][k] != -1) {
      return memo[i][j+1][k];
    }
    if(s[i] == '#') {
      if(k == 0) {
        long long int r = dp_fits(s,nums,i-1,j,1,memo);
        memo[i][j+1][k] = r;
        return r;
      } else {
        if(k < nums[j]) {
          long long int r = dp_fits(s,nums,i-1,j,k+1,memo);
          memo[i][j+1][k] = r;
          return r;
        } else {
          memo[i][j+1][k] = 0;
          return 0;
        }
      }
    } else if(s[i] == '?') {
      if(k == 0) {
        long long int a = dp_fits(s,nums,i-1,j,0,memo);
        long long int b = dp_fits(s,nums,i-1,j,1,memo);
        memo[i][j+1][k] = a+b;
        return a+b;
      } else {
        if(k == nums[j]) {
          long long int r = dp_fits(s,nums,i-1,j-1,0,memo);
          memo[i][j+1][k] = r;
          return r;
        } else if(k < nums[j]) {
          long long int r = dp_fits(s,nums,i-1,j,k+1,memo);
          memo[i][j+1][k] = r;
          return r;
        } else {
          memo[i][j+1][k] = 0;
          return 0;
        }
      }
    } else if(s[i] == '.') {
      if(k == 0) {
        long long int r = dp_fits(s,nums,i-1,j,0,memo);
        memo[i][j+1][k] = r;
        return r;
      } else {
        if(k == nums[j]) {
          long long int r = dp_fits(s,nums,i-1,j-1,0,memo);
          memo[i][j+1][k] = r;
          return r;
        } else {
          memo[i][j+1][k] = 0;
          return 0;
        }
      }
    }
  }
}

int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  int res_1 = 0;
  long res_2 = 0;

  std::vector<std::string> S;
  std::vector<std::vector<int>> SEQ;

  if(file.is_open()) {
    std::string str;
    while(getline(file, str)) {
      std::vector<int> seq;
      std::string s;
      int i;
      for(i = 0; i < str.length(); i++) {
        if(str[i] == ' ') {
          s = str.substr(0, i);
          break;
        }
      }
      i++;
      for(int j = i; j < str.length(); j++) {
        int v = stoi(str.substr(j, str.length() - j));
        j += (num_digits(v));
        seq.push_back(v);
      }
      SEQ.push_back(seq);
      S.push_back(s);
    }
    file.close();
  };

  for(int i = 0; i < S.size(); i++) {
    auto memo = create_memo(S[i].length(),SEQ[i].size(),S[i].length());
    int t = dp_fits(S[i],SEQ[i], S[i].length() - 1, SEQ[i].size() - 1, 0, memo);
    
    res_1 += t;

    std::string append = "?" + S[i];
    append = append + append;
    append = append + append;
    append = S[i] + append;
    std::vector<int> NSEQ;
    for(int j = 0; j < 5; j++) {
      for(int k = 0; k < SEQ[i].size(); k++) {
        NSEQ.push_back(SEQ[i][k]);
      }
    }

    memo = create_memo(append.length(),NSEQ.size(),append.length());

    long long int a = dp_fits(append, NSEQ, append.length() - 1, NSEQ.size() - 1, 0, memo);
    res_2 += a;
    //std::cout << "[" << i << "]: \t res_1: " << t << " \t res_2: " << a << std::endl;
  }

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}