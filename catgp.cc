#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
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
#include "../catg/decompose.hh"
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
  int  var(4);
  int  ext(8);
  bool whole(false);
  if(argc < 2)
    std::cerr << "catgp <condition>? <context>? <extcomp>? <whole|partial>?" << std::endl;
  else {
    if(1 < argc) stat  = std::atoi(argv[1]);
    if(2 < argc) var   = std::atoi(argv[2]);
    if(3 < argc) ext   = std::atoi(argv[3]);
    if(4 < argc) whole = argv[4][0] == 'w';
  }
  std::cerr << "continue with catgp " << stat << " " << var << " " << ext << " " << (const char*)(whole ? "whole" : "partial") << std::endl;
  P012L<num_t, linearFeeder<num_t>, false> pp(abs(stat), var, ext);
  P012L<num_t, linearFeeder<num_t>, true>  qp(abs(stat), var, ext);
  P012L<num_t, arctanFeeder<num_t, true>, false> pw(abs(stat), var, ext);
  P012L<num_t, arctanFeeder<num_t, true>, true>  qw(abs(stat), var, ext);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  s3(d);
  auto  M(d);
  auto  MM(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto bMM(MM);
    if(MM < abs(d))
      MM = abs(d) * num_t(2);
    if(bMM != num_t(0))
      d /= bMM;
    if(d != num_t(0)) {
      if(M != num_t(0)) {
        s0 += (s3 = d - M);
        s1 += (s2 = M / d);
      }
      M  = tan(stat < 0 ? (whole ? qw.next(atan(d)) : qp.next(atan(d)))
                        : (whole ? pw.next(atan(d)) : pp.next(atan(d))) );
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M << ", " << s0 << ", " << s1 << ", " << s2 << ", " << s3 << std::endl << std::flush;
  }
  return 0;
}

