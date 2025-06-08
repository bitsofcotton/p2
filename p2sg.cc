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
#include <random>
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
  // N.B. 1 < argc, we choose shortest length with aligning calculation
  //      timing the data first met we can combine each line.
  std::cout << std::setprecision(30);
  pslip_t<num_t> pslip(1 < argc ? 7 : 0);
  std::string s;
  int   t(0);
  num_t d(t);
  auto  M(d);
  idFeeder<num_t> in(1 < argc ? 7 : 0);
  idFeeder<num_t> bb(1 < argc ? 2 : 1);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << (M *= d) << ", " << std::flush;
    std::cout <<
      bb.next(M = pSlipGulf0short<num_t>(in.next(d), pslip, t ++) )[0] <<
        ", " << d << std::endl << std::flush;
  }
  return 0;
}

