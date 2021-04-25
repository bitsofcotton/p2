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
#include "../p0/p0.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  int stat(256);
  if(argc < 2)
    std::cerr << "catgp <condition>?" << std::endl;
  else if(1 < argc) stat = std::atoi(argv[1]);
  std::cerr << "continue with catgp " << stat << std::endl;
  P012L<num_t, false> p(2, stat);
  P0<num_t, true> q(3);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  M1(d);
  auto  M2(d);
  auto  M3(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    const auto nM(M + M1 + M2);
    const auto mM(M + M1 + M2 + M3);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd) {
      if(bd != num_t(0) && M != num_t(0)) {
        s2 += (d - bd) - (M + M1);
        s0 += (d - bd) - mM;
        s1 += (d - bd) * mM;
        M1  = d - bd - M;
        M3  = d - bd - nM;
      }
      M  = p.next(d - bd);
      M2 = q.next(s2);
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << mM << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

