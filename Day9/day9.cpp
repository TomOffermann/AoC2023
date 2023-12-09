#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

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

int calc_next(std::vector<int> data, bool is_part_two = false) {
  std::vector<std::vector<int>> tmp;
  tmp.push_back(data);
  int n = data.size();
  for(int i = 0; i < n-1; i++) {
    bool is_zero = true;
    std::vector<int> diff;
    for(int j = 0; j < n-i-1; j++) {
      int v = tmp[i][j+1]-tmp[i][j];
      diff.push_back(v);
      if(v != 0) {
        is_zero = false;
      }
    }
    tmp.push_back(diff);
    if(is_zero) break;
  }

  if(!is_part_two) {
    tmp[tmp.size()-1].push_back(0);
    for(int i = tmp.size()-2; i >= 0; i--) {
      int prev_diff = tmp[i+1][tmp[i+1].size()-1];
      tmp[i].push_back(tmp[i][tmp[i].size()-1] + prev_diff);
    } 
    
    return tmp[0][tmp[0].size()-1];
  } else {
    tmp[tmp.size()-1].insert(tmp[tmp.size()-1].begin(), 0);
    for(int i = tmp.size()-2; i >= 0; i--) {
      int prev_diff = tmp[i+1][0];
      tmp[i].insert(tmp[i].begin(), tmp[i][0] - prev_diff);
    } 
    
    return tmp[0][0];
  }
}

int main() {
  std::fstream file;
  file.open("./test.txt", std::ios::in); 

  int res_1 = 0;
  long res_2 = 0;

  std::vector<std::vector<int>> data;

  if(file.is_open()) {
    std::string str;
    while(getline(file, str)) {
      std::vector<int> line;
      for(int i = 0; i < str.size();) {
        int v = std::stoi(str.substr(i,str.length() - i));
        i += num_digits(v) + 1;
        //std::cout << v << std::endl;
        line.push_back(v);
      }
      //std::cout << "---" << std::endl;
      data.push_back(line);
    }
    file.close();
    for(int i = 0; i < data.size(); i++) {
      res_1 += calc_next(data[i]);
      res_2 += calc_next(data[i], true);
    }
  };

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}