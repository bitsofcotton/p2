#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <assert.h>
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
// N.B. we need this with shorter range.
//      after this, p0 [0-3] works well on some of tests.
// #define _PREDV_ 3
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
  int stat(80);
  if(argc < 2) std::cerr << argv[0] << " <lines>? : continue with ";
  if(1 < argc) stat = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << stat << std::endl;
  assert(0 < stat);
  idFeeder<num_t> f(abs(stat * 3));
  P0DFT<num_t, PP0<num_t> > p;
  std::string s;
  num_t d(int(0));
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    auto& fn(f.next(d));
    std::cout << (M = f.full ? p.next(fn, abs(stat)) : num_t(int(0)) ) << std::endl << std::flush;
  }
  return 0;
}

