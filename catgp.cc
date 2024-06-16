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
  int progression(1);
  if(argc < 2) std::cerr << argv[0] << " <status>? <progression num>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  if(2 < argc) progression = std::atoi(argv[2]);
  std::cerr << argv[0] << " " << status << " " << progression << std::endl;
  assert(0 < status);
  // N.B. randtools meaning, v2v tanglement causes up to 3 dimension.
  //      This is also from P1I condition this uses internally.
  Pprogression<num_t, PBond<num_t, P012L<num_t> > > p(PBond<num_t, P012L<num_t> >(P012L<num_t>(min(int(4), int(max(num_t(int(1)), pow(num_t(status), num_t(int(1)) / num_t(int(3))) ))) ), status), progression);
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

