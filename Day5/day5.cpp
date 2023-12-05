#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <algorithm>

int num_digits(long x)  
{  
    x = abs(x);  
    return (x < 10 ? 1 :   
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

struct map {
  long dest_start;
  long source_start;
  long range;
};

long get_val(struct map a, long b) {
  if(b >= a.source_start && b <= a.source_start + a.range) {
    return a.dest_start + (b - a.source_start);
  }
  return b;
}

void print(std::vector<struct map> v) {
  for(int i = 0; i < v.size(); i++) {
    std::cout << "[" << v[i].source_start << "," << v[i].source_start + v[i].range - 1 << "] -> [" << v[i].dest_start << "," << v[i].dest_start + v[i].range - 1 << "] \n";
  }
}

int main() {
  std::fstream file;
  file.open("./test.txt", std::ios::in); 

  long res_1 = 1000000000000000;
  long res_2 = 1000000000000000;

  std::vector<long> seeds;
  std::vector<long> seeds1;
  std::vector<std::vector<struct map>> maps;

  if(file.is_open()) {
    std::string str;

    std::vector<struct map> vals;

    while(getline(file, str)) {
      if(str.substr(0,5) == "seeds") {
        for(int i = 7; i < str.length();) {
          long x = std::stol(str.substr(i, str.length() - i));
          seeds.push_back(x);
          seeds1.push_back(x);
          i += (num_digits(x) + 1);
        }
      } else {
        bool is_new = false;
        for(int i = 0; i < str.length(); i++) {
          if(str[i] == ':') {
            is_new = true;
          }
        }
        if(!is_new && str.length() > 0) {
          int i = 0;
          struct map tmp;
          tmp.dest_start = std::stol(str);
          i += num_digits(tmp.dest_start)+1;
          tmp.source_start = std::stol(str.substr(i,str.length()-i));
          i += num_digits(tmp.source_start)+1;
          tmp.range = std::stol(str.substr(i,str.length()-i));
          vals.push_back(tmp);
        }

        if(str.length() == 0) {
          maps.push_back(vals);
          vals.clear();
        }
      }
    }
    file.close();
  };


  for(int i = 0; i < maps.size(); i++) {
    for(int k = 0; k < seeds.size(); k++) {
      bool found = false;
      long val;
      for(int j = 0; !found && j < maps[i].size(); j++) {
        if(get_val(maps[i][j], seeds[k]) != seeds[k]) {
          found = true;
          val = get_val(maps[i][j], seeds[k]);
        }
      }
      if(found){
        seeds[k] = val;
      };
    }
  }

  for(int i = 0; i < seeds.size(); i++) {
    res_1 = std::min(res_1, seeds[i]);
  }

  // bruteforce bullshit solution :(, run with -O3 to wait under a minute
  for(int seed = 0; seed < seeds1.size(); seed+=2) {
    std::cout << seed << std::endl;
    for(long v = 0; v < seeds1[seed+1]; v++) {
      long tmp = seeds1[seed] + v;
      for(int i = 0; i < maps.size(); i++) {
        for(int j = 0; j < maps[i].size(); j++) {
          if(get_val(maps[i][j], tmp) != tmp) {
            tmp = get_val(maps[i][j], tmp);
            break;
          }
        }
      }
      res_2 = std::min(res_2, tmp);
    }
  }
  
  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 - 1 << std::endl;
}