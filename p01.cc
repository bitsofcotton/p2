#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <assert.h>

#include "../p1/ifloat.hh"
typedef myfloat num_t;
#include "../p1/simplelin.hh"
#include "../p0/p0.hh"
#include "../p1/p1.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  int vrange(12);
  int eslen(0);
  int ratio(20);
  if(argc < 3) {
    std::cerr << "p01 <variable> <extra>? <ratio>?" << std::endl;
    std::cerr << "continue with p01 " << vrange << " " << eslen << " " << ratio << std::endl;
  } else {
    vrange = std::atoi(argv[1]);
    if(2 < argc) eslen = std::atoi(argv[2]);
    if(3 < argc) ratio = std::atoi(argv[3]);
  }
  assert(0 <= eslen);
  P0<num_t>  p(abs(vrange));
  P1I<num_t> q(eslen, vrange);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd) {
      if(bd != num_t(0) && M != num_t(0)) {
        s0 += (d - bd) - M;
        s1 += (d - bd) * M;
      }
      const auto pn(p.next(d) - d);
      M = pn - q.next(d - bd, ratio);
      if(! isfinite(M) || isnan(M)) M = pn;
    }
    std::cout << M << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

