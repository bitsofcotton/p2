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
  int progression0(1);
  if(argc < 2) std::cerr << argv[0] << " <progression num>? : continue with ";
  if(1 < argc) progression0 = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << progression0 << std::endl;
  assert(progression0);
  const auto progression(abs(progression0));
  // N.B. randtools meaning, v2v tanglement causes up to 3 dimension.
  //      This is also from P1I condition this uses internally.
  P210<num_t> p(
    Pprogression<num_t, PBond<num_t, P012L<num_t> > >(
      PBond<num_t, P012L<num_t> >(P012L<num_t>(4), 124), progression),
    PAthenB<num_t, Pprogression<num_t, PBond<num_t, P01<num_t> > >,
      Pprogression<num_t, PBond<num_t, P0maxRank<num_t> > >  >(
        Pprogression<num_t, PBond<num_t, P01<num_t> > >(
          PBond<num_t, P01<num_t> >(P01<num_t>(4), 28), progression),
        Pprogression<num_t, PBond<num_t, P0maxRank<num_t> > >(
          PBond<num_t, P0maxRank<num_t> >(P0maxRank<num_t>(), 3), progression)
      ) );
  std::string s;
  num_t d(int(0));
  auto  M(d);
  auto  S(d);
  while(progression0 < 0 ? true : bool(std::getline(std::cin, s, '\n'))) {
    if(progression0 < 0) {
      d = num_t(arc4random_uniform(0x2001)) - num_t(0x1000);
      std::cout << (S += d * M) << std::endl << std::flush;
      M = p.next(d);
    } else {
      std::stringstream ins(s);
      ins >> d;
      std::cout << d * M << ", ";
      std::cout << (M = p.next(d)) << std::endl << std::flush;
    }
  }
  return 0;
}

