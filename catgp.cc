#include <cstdio>
#include <cstring>
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
  int   stat(200);
  num_t inten0(- num_t(1) / sqrt(num_t(2)));
  num_t inten1(- num_t(1) / sqrt(num_t(2)));
  if(argc < 2)
    std::cerr << "catgp <condition>? <intensity0>? <intensity1>?" << std::endl;
  else {
    if(1 < argc) stat   = std::atoi(argv[1]);
    // XXX: atof.
    if(2 < argc) inten0 = std::atof(argv[2]);
    if(3 < argc) inten1 = std::atof(argv[3]);
  }
  std::cerr << "continue with catgp " << stat << " " << inten0 << " " << inten1 << std::endl;
  P012L<num_t, false> p(2, stat, inten0);
  P012L<num_t, false> q(2, stat, inten1);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  M0(d);
  auto  M(d);
  auto  bdelta(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd) {
      if(bd != num_t(0) && M0 != num_t(0)) {
        s2 = (d - bd) - M0;
        if(M != num_t(0)) {
          s1 += (d - bd) * (M + bdelta);
          s0 += (bdelta = (d - bd) - M);
        }
      }
      M = (M0 = p.next(d - bd)) + q.next(s2);
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M + bdelta << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

