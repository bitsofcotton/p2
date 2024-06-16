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
  int progression(1);
  if(argc < 2) std::cerr << argv[0] << " <progression num>? : continue with ";
  if(1 < argc) progression = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << progression << std::endl;
  assert(progression);
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
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    std::cout << (M = p.next(d)) << std::endl << std::flush;
  }
  return 0;
}

