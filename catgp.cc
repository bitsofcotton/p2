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
  int stat(256);
  int var(8);
  if(argc < 2)
    std::cerr << "catgp <condition>? <context>?" << std::endl;
  else {
    if(1 < argc) stat = std::atoi(argv[1]);
    if(2 < argc) var  = std::atoi(argv[2]);
  }
  std::cerr << "continue with catgp " << stat << " " << var << std::endl;
  P012L<num_t, false> p(stat, var);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  M0(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    const auto nM(M + M0);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd) {
      if(bd != num_t(0) && M != num_t(0)) {
        s0 += (d - bd) - nM;
        s1 += (d - bd) * nM;
        M0  = d - bd - M;
      }
      M  = p.next(d) - d;
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << nM << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

