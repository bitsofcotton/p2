#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <random>
#include <assert.h>
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  std::random_device rd;
  std::mt19937_64 mt(rd());
  std::knuth_b    kb(rd());
  std::ranlux48   rl48(rd());
  num_t M(int(0));
  auto  S(M);
  idFeeder<num_t> v(63);
  while(true) {
    const auto d(
       ((num_t(((int(rd()) ^ int(mt()) ^ int(kb()) ^ int(rl48())) >> 1)
               & 0x7fffffff) / (num_t(int(0x7fffffff)) / num_t(int(2)))
        - num_t(int(1))) ) * pow(num_t(int(10)), - num_t(int(6))) );
    std::cout << (S += d * M) << std::endl << std::flush;
    const auto& res(v.next(d));
    M = num_t(int(0));
    if(v.full)
      for(int i = 5; i < res.size(); i ++)
        M += Prange<num_t>(i).next(res.subVector(res.size() - i, i));
    if(rd() & 1) rd();
    if(rd() & 1) rd();
    if(mt() & 1) mt();
    if(mt() & 1) mt();
    if(kb() & 1) kb();
    if(kb() & 1) kb();
    if(rl48() & 1) rl48();
    if(rl48() & 1) rl48();
  }
  return 0;
}

