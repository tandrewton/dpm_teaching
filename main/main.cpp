#include "dpm.h"
#include <iostream>
#include <vector>

// navigate to dpm_teaching folder in command line
// compilation command: g++ -O3 --std=c++11 -I src main/main.cpp src/dpm.cpp -o main/main.o
// run command: ./main/main.o

// preprocessor macros
using namespace std;

int main(){
  cout << "Hello world!\n";
  std::vector<bool> boolVec;
  int a = 1, b = 2;
  boolVec.push_back(isEven(a));
  boolVec.push_back(isEven(b));
  for (int i = 0; i < boolVec.size(); i++){
    cout << "boolVec[" << i << "] = " << boolVec[i] << '\n';
  }
  return 0;
}
