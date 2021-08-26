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
  return res / num_t(0x1000);
}

int main(int argc, char* argv[]) {
  assert(5 <= argc);
  std::random_device rnd;
  std::mt19937 mt(rnd());
  auto  cnt(std::atoi(argv[4]));
  num_t s0(0);
  for(int i = 0; cnt < 0 || i < cnt; i ++) {
    if(std::atoi(argv[3])) {
      num_t s(0);
      num_t r(1);
      for(int j = 0; j < std::atoi(argv[3]); j ++)
        s += mmt(mt, std::atoi(argv[1]), std::atoi(argv[2])) *
             (r *= mmt(mt, std::atoi(argv[1]), std::atoi(argv[2])));
      std::cout << (s0 += s * r) << std::endl;
    } else
      std::cout << (s0 += mmt(mt, std::atoi(argv[1]), std::atoi(argv[2]))) << std::endl;
  }
  return 0;
}

