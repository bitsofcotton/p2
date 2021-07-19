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

num_t mmt(std::mt19937& mt, bool arc4 = false, int c = 3) {
  int res(0);
  for(int i = 0; i < c; i ++)
    res = num_t(int(arc4 ? arc4random_uniform(0x8000) : mt() % 0x8000) -
            int(0x4000)) + num_t(1) / num_t(2);
  return res;
}

int main(int argc, char* argv[]) {
  assert(5 <= argc);
  std::random_device rnd;
  std::mt19937 mt(rnd());
  auto cnt(std::atoi(argv[4]));
  for(int i = 0; cnt < 0 || i < cnt; i ++) {
    if(std::atoi(argv[3])) {
      num_t s(0);
      for(int i = 0; i < std::atoi(argv[3]); i ++) {
        num_t r(0);
        for(int j = 0; j < std::atoi(argv[3]); j ++)
          r += mmt(mt, std::atoi(argv[1]), std::atoi(argv[2])) *
               mmt(mt, std::atoi(argv[1]), std::atoi(argv[2]));
        s += r * mmt(mt, std::atoi(argv[1]), std::atoi(argv[2]));
      }
      if(num_t(0) <= s)
        std::cout <<   pow(  s, num_t(1) / num_t(3)) << std::endl;
      else
        std::cout << - pow(- s, num_t(1) / num_t(3)) << std::endl;
    } else
      std::cout << mmt(mt, std::atoi(argv[1]), std::atoi(argv[2])) << std::endl;
  }
  return 0;
}

