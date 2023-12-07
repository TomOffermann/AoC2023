#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

// This might be the worst code I ever wrote : )

template<typename T>
void print(std::vector<T> a) {
  for(int i = 0; i < a.size(); i++) {
    std::cout << a[i];
    if(i != a.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
}

int compareStr(std::string a, std::string b) {
  std::unordered_map<char, int> ranking =
    {
        {'A', 12},
        {'K', 11},
        {'Q', 10},
        {'J', 9},
        {'T', 8},
        {'9', 7},
        {'8', 6},
        {'7', 5},
        {'6', 4},
        {'5', 3},
        {'4', 2},
        {'3', 1},
        {'2', 0},
    };
  
  std::unordered_map<char, int> a_occ =
    {
        {'A', 0},
        {'K', 0},
        {'Q', 0},
        {'J', 0},
        {'T', 0},
        {'9', 0},
        {'8', 0},
        {'7', 0},
        {'6', 0},
        {'5', 0},
        {'4', 0},
        {'3', 0},
        {'2', 0},
    };

  std::unordered_map<char, int> b_occ =
    {
        {'A', 0},
        {'K', 0},
        {'Q', 0},
        {'J', 0},
        {'T', 0},
        {'9', 0},
        {'8', 0},
        {'7', 0},
        {'6', 0},
        {'5', 0},
        {'4', 0},
        {'3', 0},
        {'2', 0},
    };

  for(int i = 0; i < 5; i++) {
    a_occ[a[i]]++;
    b_occ[b[i]]++;
  }

  int type_a, type_b;
  type_a = 0;
  type_b = 0;
  bool a_has2 = false, a_has22 = false, a_has3 = false;
  bool b_has2 = false, b_has22 = false, b_has3 = false;
  for(const std::pair<const char, int>& p : a_occ) {
    if(p.second == 5) {
      type_a = 7;
    } else if(p.second == 4) {
      type_a = 6;
    } else if(p.second == 3) {
      a_has3 = true;
    } else if(p.second == 2) {
      if(a_has2) {
        a_has22 = true;
      } else {
        a_has2 = true;
      }
    }
    //std::cout << a_has3 << " " << a_has2 << " " << a_has22 << "\n";
  
  }
  //std::cout << a_has3 << " " << a_has2 << " " << a_has22 << "\n";
  if(type_a == 0) {
    if(a_has3 && a_has2) {
      type_a = 5;
    } else if(a_has3) {
      type_a = 4;
    } else if(a_has2 && a_has22) {
      type_a = 3;
    } else if(a_has2) {
      type_a = 2;
    } else {
      type_a = 1;
    }
  }
  for(const std::pair<const char, int>& p : b_occ) {
    if(p.second == 5) {
      type_b = 7;
    } else if(p.second == 4) {
      type_b = 6;
    } else if(p.second == 3) {
      b_has3 = true;
    } else if(p.second == 2) {
      if(b_has2) {
        b_has22 = true;
      }
      b_has2 = true;
    }
  }
  if(type_b == 0) {
    if(b_has3 && b_has2) {
      type_b = 5;
    } else if(b_has3) {
      type_b = 4;
    } else if(b_has2 && b_has22) {
      type_b = 3;
    } else if(b_has2) {
      type_b = 2;
    } else {
      type_b = 1;
    }
  }
  //std::cout << type_a << " " << type_b << "\n";
  if(type_a - type_b != 0) {
    return type_a - type_b;
  } else {
    for(int i = 0; i < 5; i++) {
      if(ranking[a[i]] - ranking[b[i]] != 0) {
        return ranking[a[i]] - ranking[b[i]];
      }
    }
    return 0;
  }
}

int compareStrJ(std::string a, std::string b) {
  std::unordered_map<char, int> ranking =
    {
        {'A', 12},
        {'K', 11},
        {'Q', 10},
        {'J', 0},
        {'T', 9},
        {'9', 8},
        {'8', 7},
        {'7', 6},
        {'6', 5},
        {'5', 4},
        {'4', 3},
        {'3', 2},
        {'2', 1},
    };
  
  std::unordered_map<char, int> a_occ =
    {
        {'A', 0},
        {'K', 0},
        {'Q', 0},
        {'J', 0},
        {'T', 0},
        {'9', 0},
        {'8', 0},
        {'7', 0},
        {'6', 0},
        {'5', 0},
        {'4', 0},
        {'3', 0},
        {'2', 0},
    };

  std::unordered_map<char, int> b_occ =
    {
        {'A', 0},
        {'K', 0},
        {'Q', 0},
        {'J', 0},
        {'T', 0},
        {'9', 0},
        {'8', 0},
        {'7', 0},
        {'6', 0},
        {'5', 0},
        {'4', 0},
        {'3', 0},
        {'2', 0},
    };
  int numJokersA = 0, numJokersB = 0;
  for(int i = 0; i < 5; i++) {
    if(a[i] == 'J') {
      numJokersA++;
    }
    if(b[i] == 'J') {
      numJokersB++;
    }
    a_occ[a[i]]++;
    b_occ[b[i]]++;
  }

  int type_a, type_b;
  type_a = 0;
  type_b = 0;
  bool a_has2 = false, a_has22 = false, a_has3 = false;
  bool b_has2 = false, b_has22 = false, b_has3 = false;
  for(const std::pair<const char, int>& p : a_occ) {
    if(p.second == 5) {
      type_a = 7;
    } else if(p.second == 4) {
      if(numJokersA == 1 || numJokersA == 4) {
        type_a = 7;
      } else {
        type_a = 6;
      }
    } else if(p.second == 3) {
      a_has3 = true;
    } else if(p.second == 2) {
      if(a_has2) {
        a_has22 = true;
      } else {
        a_has2 = true;
      }
    }
  }
  if(type_a == 0) {
    if(a_has3 && a_has2) {
      if(numJokersA == 2 || numJokersA == 3) {
        type_a = 7;
      } else {
        type_a = 5;
      }
    } else if(a_has3) {
      if(numJokersA == 3 || numJokersA == 1) {
        type_a = 6;
      } else {
        type_a = 4;
      }
    } else if(a_has2 && a_has22) {
      if(numJokersA == 1) {
        type_a = 5;
      } else if(numJokersA == 2) {
        type_a = 6;
      } else {
        type_a = 3;
      }
    } else if(a_has2) {
      if(numJokersA == 1 || numJokersA == 2) {
        type_a = 4;
      } else {
        type_a = 2;
      }
    } else {
      if(numJokersA == 1) {
        type_a = 2;
      } else {
        type_a = 1;
      }
    }
  }
  for(const std::pair<const char, int>& p : b_occ) {
    if(p.second == 5) {
      type_b = 7;
    } else if(p.second == 4) {
      if(numJokersB == 1 || numJokersB == 4) {
        type_b = 7;
      } else {
        type_b = 6;
      }
    } else if(p.second == 3) {
      b_has3 = true;
    } else if(p.second == 2) {
      if(b_has2) {
        b_has22 = true;
      } else {
        b_has2 = true;
      }
    }
  }
  if(type_b == 0) {
    if(b_has3 && b_has2) {
      if(numJokersB == 2 || numJokersB == 3) {
        type_b = 7;
      } else {
        type_b = 5;
      }
    } else if(b_has3) {
      if(numJokersB == 3 || numJokersB == 1) {
        type_b = 6;
      } else {
        type_b = 4;
      }
    } else if(b_has2 && b_has22) {
      if(numJokersB == 1) {
        type_b = 5;
      } else if(numJokersB == 2) {
        type_b = 6;
      } else {
        type_b = 3;
      }
    } else if(b_has2) {
      if(numJokersB == 1 || numJokersB == 2) {
        type_b = 4;
      } else {
        type_b = 2;
      }
    } else {
      if(numJokersB == 1) {
        type_b = 2;
      } else {
        type_b = 1;
      }
    }
  }
  if(type_a - type_b != 0) {
    return type_a - type_b;
  } else {
    for(int i = 0; i < 5; i++) {
      if(ranking[a[i]] - ranking[b[i]] != 0) {
        return ranking[a[i]] - ranking[b[i]];
      }
    }
    return 0;
  }
}


int main() {
  std::fstream file;
  file.open("./input.txt", std::ios::in); 

  long res_1 = 0;
  long res_2 = 0;

  std::vector<std::pair<std::string,int>> tickets;

  if(file.is_open()) {
    std::string str;

    while(getline(file, str)) {
      std::pair<std::string,int> t;
      t.first = str.substr(0,5);
      t.second = std::stoi(str.substr(5,str.length() - 5));
      tickets.push_back(t);
    };
    
    std::sort(tickets.begin(), tickets.end(), [](std::pair<std::string,int> &left, std::pair<std::string,int> &right) {
      return compareStr(left.first, right.first) < 0;
    });
    
    for(int i = 0; i < tickets.size(); i++) {
      res_1 += (i+1) * tickets[i].second;
    }

    std::sort(tickets.begin(), tickets.end(), [](std::pair<std::string,int> &left, std::pair<std::string,int> &right) {
      return compareStrJ(left.first, right.first) < 0;
    });
    
    for(int i = 0; i < tickets.size(); i++) {
      res_2 += (i+1) * tickets[i].second;
    }

    file.close();
  };

  std::cout << "Task 1: " << res_1 << ", Task 2: " << res_2 << std::endl;
}