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
  int status(124);
  if(argc < 2) std::cerr << argv[0] << " <status>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << status << std::endl;
  assert(0 <= status);
  PBond<num_t, P0maxRank<num_t> > p0(P0maxRank<num_t>(), 3);
  PBond<num_t, P01<num_t> > p1(P01<num_t>(4), 28);
  // N.B. randtools meaning, v2v tanglement causes up to 3 dimension.
  //      This is also from P1I condition this uses internally.
  PBond<num_t, P012L<num_t> > p(P012L<num_t>(status ? min(int(4), int(max(num_t(int(1)), pow(num_t(status), num_t(int(1)) / num_t(int(3))) ))) : 4), status ? status : 124);
  std::string s;
  num_t d(int(0));
  auto  M(d);
  auto  M2(d);
  auto  M1(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    if(status) M = p.next(d);
    else {
      const auto d1(M2 * d);
      const auto d2(M2 * M1 * d);
      M2 = p.next(d);
      M1 = p1.next(d1);
      M  = M2 * M1 * p0.next(d2);
    }
    std::cout << M << std::endl << std::flush;
  }
  return 0;
}

