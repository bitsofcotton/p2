#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <assert.h>

#include "../catg/ifloat.hh"
typedef myfloat num_t;
#include "../catg/simplelin.hh"
#include "../catg/decompose.hh"
#include "../catg/catg.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  int stat(256);
  if(argc < 2)
    std::cerr << "catgp <condition>?" << std::endl;
  else if(1 < argc) stat = std::atoi(argv[1]);
  std::cerr << "continue with catgp " << stat << std::endl;
  P012L<num_t, false> p(2, stat);
  auto  q(p);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  s3(d);
  auto  M0(d);
  auto  M(d);
  auto  bdelta(d);
  auto  cdelta(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    const auto bbd(bdelta);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd) {
      if(bd != num_t(0) && M0 != num_t(0)) {
        s2 = (d - bd) - M0;
        if(M != num_t(0)) {
          s0 += (d - bd) - (M + bdelta - cdelta);
          s1 += (d - bd) * (M + bdelta - cdelta);
          cdelta = (d - bd) - (M + bdelta);
          bdelta = (d - bd) - M;
        }
      }
      M = (M0 = p.next(d - bd)) + q.next(s2);
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M + bdelta - cdelta << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

