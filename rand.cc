#include <random>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <assert.h>

#include "../catg/lieonn.hh"
typedef myfloat num_t;
// typedef double num_t;

num_t mmt(std::mt19937& mt, bool arc4 = false) {
  return (num_t(int(arc4 ? arc4random_uniform(0x8000) : mt() % 0x8000) -
           int(0x4000)) + num_t(1) / num_t(2)) / num_t(0x1000);
}

int main(int argc, char* argv[]) {
  assert(2 < argc);
  std::random_device rnd;
  std::mt19937 mt(rnd());
  const auto cnt(std::atoi(argv[2]));
  for(int i = 0; cnt < 0 || i < cnt; i ++) {
    if(1 < abs(std::atoi(argv[1]))) {
      num_t s(0);
      for(int j = 0; j < abs(std::atoi(argv[1])) - 1; j ++)
        s += mmt(mt, std::atoi(argv[1]) < 0) *
             mmt(mt, std::atoi(argv[1]) < 0);
      s += num_t(0x4);
      s -= floor(s / num_t(0x8)) * num_t(0x8);
      s -= num_t(0x4);
      std::cout << s << std::endl;
    } else
      std::cout << mmt(mt, std::atoi(argv[1]) < 0) << std::endl;
  }
  return 0;
}

