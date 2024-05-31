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
  assert(0 < status);
  // N.B. randtools meaning, v2v tanglement causes up to 3 dimension.
  //      This is also from P1I condition this uses internally.
  PBond<num_t, P012L<num_t> > p(P012L<num_t>(min(int(4), int(max(num_t(int(1)), pow(num_t(status), num_t(int(1)) / num_t(int(3))) )))), status);
  std::string s;
  num_t d(int(0));
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
#if defined(_JAM_)
    if(M != num_t(int(0))) d = abs(d) * sgn<num_t>(arc4random_uniform(2) & 1 ? - M : M);
    M = p.next(d);
    std::cout << d << std::endl << std::flush;
#else
    std::cout << d * M << ", ";
    std::cout << (M = p.next(d)) << std::endl << std::flush;
#endif
  }
  return 0;
}

