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
  int length(124);
  int step(1);
  if(argc < 2) std::cerr << argv[0] << " <length>? <step>? : continue with ";
  if(1 < argc) length = std::atoi(argv[1]);
  if(2 < argc) step   = std::atoi(argv[2]);
  assert(length && 0 < step);
  std::cerr << argv[0] << " " << length << " " << step << std::endl;
  // N.B. randtools meaning, v2v tanglement causes up to 3 dimension.
  //      This is also from P1I condition this uses internally.
  PBond<num_t, P012L<num_t> > p(abs(length), P012L<num_t>(step));
  idFeeder<num_t> f(step);
  std::string s;
  num_t d(int(0));
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto& M(f.res[0]);
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    std::cout << f.next(p.next(d))[f.res.size() - 1] << std::endl << std::flush;
  }
  return 0;
}

