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
  int step(1);
  int length(0);
  if(argc < 2) std::cerr << argv[0] << " <step>? <length>? : continue with ";
  if(1 < argc) step   = std::atoi(argv[1]);
  if(2 < argc) length = std::atoi(argv[2]);
  std::cerr << argv[0] << " " << step << " " << length << std::endl;
  assert(0 < step && 0 <= length);
  // N.B. randtools meaning, v2v tanglement causes up to 3 dimension.
  //      This is also from P1I condition this uses internally.
  PBond<num_t, P012L<num_t> > p(max(1, length), P012L<num_t>());
  idFeeder<num_t> f(step);
  SimpleVector<num_t> b;
  std::string s;
  num_t d(int(0));
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    const auto& M(f.res[0]);
    ins >> d;
#if defined(_CHAIN_)
    std::cout << d - M << ", ";
#else
    std::cout << d * M << ", ";
#endif
    if(! length) {
      b.entity.emplace_back(d);
      if(3 < b.size())
        f.next(P012L<num_t>().next(b));
    } else f.next(p.next(d));
    std::cout << f.res[step - 1] << std::endl << std::flush;
  }
  return 0;
}

