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
  std::cout << std::setprecision(30);
  pslip_t<num_t> pslip;
  std::string s;
  int   t(0);
  num_t d(t);
  auto  M(d);
  idFeeder<num_t> in(0);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << (M *= d) << ", " << std::flush;
    std::cout <<
      (M = pSlipGulf0short<num_t>(in.next(d), pslip, t ++) ) << ", " << d <<
        std::endl << std::flush;
  }
  return 0;
}

