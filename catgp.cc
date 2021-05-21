#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <assert.h>

#include "../catg/lieonn.hh"
typedef myfloat num_t;
#include "../catg/decompose.hh"
#include "../catg/catg.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  int  stat(256);
  int  var(4);
  bool whole(false);
  if(argc < 2)
    std::cerr << "catgp <condition>? <context>? <whole|partial>?" << std::endl;
  else {
    if(1 < argc) stat  = std::atoi(argv[1]);
    if(2 < argc) var   = std::atoi(argv[2]);
    if(3 < argc) whole = argv[3][0] == 'w';
  }
  std::cerr << "continue with catgp " << stat << " " << var << " " << (const char*)(whole ? "whole" : "partial") << std::endl;
  P012L<num_t, linearFeeder<num_t>, false> pp(abs(stat), var);
  P012L<num_t, linearFeeder<num_t>, true>  qp(abs(stat), var);
  P012L<num_t, arctanFeeder<num_t, true>, false> pw(abs(stat), var);
  P012L<num_t, arctanFeeder<num_t, true>, true>  qw(abs(stat), var);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    if(d) {
      if(bd != num_t(0) && M != num_t(0)) {
        s0 += d - M;
        s1 += (s2 = d * M);
      }
      M  = stat < 0 ? (whole ? qw.next(d) : qp.next(d))
                    : (whole ? pw.next(d) : pp.next(d));
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M << ", " << s0 << ", " << s1 << ", " << s2 << std::endl << std::flush;
  }
  return 0;
}

