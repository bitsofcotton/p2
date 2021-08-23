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

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "../catg/lieonn.hh"
typedef myfloat num_t;
#include "../catg/catg.hh"

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  int  stat(256);
  int  var(3);
  if(argc < 2)
    std::cerr << "catgp <condition>? <var>?" << std::endl;
  else {
    if(1 < argc) stat = std::atoi(argv[1]);
    if(2 < argc) var  = std::atoi(argv[2]);
  }
  std::cerr << "continue with catgp " << stat << " " << var << std::endl;
  P012L<num_t, linearFeeder<num_t> > p(abs(stat), abs(var));
  P012L<num_t, arctanFeeder<num_t> > q(abs(stat), abs(var));
  std::string s;
  num_t d(0);
  auto  M(d);
  auto  S(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd) {
      S += (d - bd) * (var < 0 ? sgn(M) : M);
      M  = (stat < 0 ? q.next(d) : p.next(d)) - d;
    }
    std::cout << S << ", " << M << std::endl << std::flush;
  }
  return 0;
}

