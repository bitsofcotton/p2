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
  P012L<num_t, continuousFeeder<num_t, continuousFeeder<num_t, linearFeeder<num_t> > > > p(abs(stat), abs(var));
  P012L<num_t, continuousFeeder<num_t, continuousFeeder<num_t, arctanFeeder<num_t> > > > q(abs(stat), abs(var));
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  s3(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    if(d != num_t(0)) {
      if(M != num_t(0)) {
        s0 += (s3 = (d - bd) - (M - d));
        s1 += (s2 = (d - bd) * (M - d));
      }
      M  = tan(stat < 0 ? q.next(atan(d)) : p.next(atan(d)));
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M - d << ", " << s0 << ", " << s1 << ", " << s2 << ", " << s3 << std::endl << std::flush;
  }
  return 0;
}

