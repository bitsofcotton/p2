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
#include <stdint.h>
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
  // N.B. this is enough when we apply eigen vectors they break low of
  //      excluded middle to in/output, however, this is raw for them.
  int stat(729);
  if(argc < 2) std::cerr << argv[0] << " <stat>? : continue with ";
  if(1 < argc) stat  = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << stat << std::endl;
  assert(9 <= stat);
  Persistent<num_t> p(stat);
  num_t d(int(0));
  auto  M(d);
  std::string s;
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << (M == num_t(int(0)) ? M : d - M) << ", " << d - M << ", " << d * M << ", ";
    std::cout << (M = p.next(d)) << std::endl << std::flush;
  }
  return 0;
}

