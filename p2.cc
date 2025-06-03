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
#include <random>
#include <assert.h>
#include <sys/resource.h>

/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
#include "lieonn.hh"
typedef myfloat num_t;
/*
#if defined(_FLOAT_BITS_)
#undef int
#endif
*/
int main(int argc, const char* argv[]) {
/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
  std::cout << std::setprecision(30);
  idFeeder<num_t> p0, p1;
  idFeeder<SimpleVector<num_t> > f0, f1;
  idFeeder<num_t> r0, r1;
  std::string s;
  int   t(0);
  num_t d(t);
  auto  M(d);
  auto  br0(d);
  vector<num_t> lastM;
  lastM.resize(6, num_t(int(0)) );
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
#if defined(_CHAIN_)
    std::cout << d - M << ", ";
#else
    std::cout << d * M << ", ";
#endif
#if defined(_NONLINEAR_X_)
    p2next<num_t, true >(lastM, p0.next(d), p1, f0, f1, r0, r1, br0, t);
#else
    p2next<num_t, false>(lastM, p0.next(d), p1, f0, f1, r0, r1, br0, t);
#endif
    auto& MM(lastM);
    std::cout << (M = MM[0] * MM[1] * MM[2] * MM[3] * MM[4] * MM[5]) << std::endl << std::flush;
//    std::cout << (isfinite(M) ? M : M = num_t(int(0)) ) << std::endl << std::flush;
  }
  return 0;
}

