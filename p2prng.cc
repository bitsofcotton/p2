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
#if defined(_GETENTROPY_)
#include <unistd.h>
#endif

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
#if defined(_BIT_)
    // XXX: ud(...) <= 2 case is not handled.
    std::cout << num_t(int(arc4random_uniform(3)) - 1) << ", ";
    std::cout << num_t(ud(er) % 3 - 1) << ",";
    std::cout << num_t(ud(mt) % 3 - 1) << ",";
    std::cout << num_t(ud(rl24) % 3 - 1) << ",";
    std::cout << num_t(ud(rl48) % 3 - 1) << ",";
    std::cout << num_t(ud(kb) % 3 - 1) << ",";
# if defined(_GETENTROPY_)
    uint8_t rnd[4];
    for(int i = 0; i < 1600000 / 4; i ++)
      getentropy(rnd, sizeof rnd);
    std::cout << num_t(((int32_t&)(*rnd) % 3) - 1);
# endif
#else
    std::cout << fl(int(arc4random_uniform(0x2001)) - 0x1000, 0x1000) << ",";
    std::cout << fl(ud(er) - 0x1000, 0x1000) << ",";
    std::cout << fl(ud(mt) - 0x1000, 0x1000) << ",";
    std::cout << fl(ud(rl24) - 0x1000, 0x1000) << ",";
    std::cout << fl(ud(rl48) - 0x1000, 0x1000) << ",";
    std::cout << fl(ud(kb) - 0x1000, 0x1000) << ",";
# if defined(_GETENTROPY_)
    uint8_t rnd[4];
    for(int i = 0; i < 1600000 / 4; i ++)
      getentropy(rnd, sizeof rnd);
    // XXX: [-1,1[ case, we in fact need: [-1,1].
    std::cout << fl(((uint32_t&)(*rnd) & 0x1fff) - 0x1000, 0x1000);
# endif
#endif
    std::cout << std::endl << std::flush;
  }
  return 0;
}

