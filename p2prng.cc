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
#include <stdint.h>
#include <sys/resource.h>

#include <random>

#include "lieonn.hh"
typedef myfloat num_t;

static inline num_t fl(int x, int M) {
  return num_t(x) / num_t(M + 1);
}

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  std::random_device r;
  std::default_random_engine er(r());
  std::mt19937 mt(r());
  std::ranlux24 rl24(r());
  std::ranlux48 rl48(r());
  std::knuth_b kb(r());
  std::uniform_int_distribution<int> ud(0, 0x2000);
  while(true) {
    std::cout << fl(int(arc4random_uniform(0x2001)) - 0x1000, 0x1000) << ",";
    std::cout << fl(ud(er) - 0x1000, 0x1000) << ",";
    std::cout << fl(ud(mt) - 0x1000, 0x1000) << ",";
    std::cout << fl(ud(rl24) - 0x1000, 0x1000) << ",";
    std::cout << fl(ud(rl48) - 0x1000, 0x1000) << ",";
    std::cout << fl(ud(kb) - 0x1000, 0x1000) << std::endl << std::flush;
  }
  return 0;
}

