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
  int pcount(520);
  if(argc < 2)
    std::cerr << "catgp <pred_count>?" << std::endl;
  else if(1 < argc) pcount = std::atoi(argv[1]);
  std::cerr << "continue with catgp " << pcount << std::endl;
  std::vector<P012L<num_t, false> > p;
  for(int i = 8; i < pcount; i *= 2)
    p.emplace_back(P012L<num_t, false>(2, i));
  auto  q(p);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  M0(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd) {
      if(bd != num_t(0) && M0 != num_t(0)) {
        s2 = (d - bd) - M0;
        if(M != num_t(0)) {
          s0 += (d - bd) - M;
          s1 += (d - bd) * M;
        }
      }
      M0 = num_t(0);
      for(int i = 0; i < p.size(); i ++)
        M0 += p[i].next(d - bd);
      M0 /= num_t(p.size());
      M  = num_t(0);
      for(int i = 0; i < q.size(); i ++)
        M  += q[i].next(s2);
      M /= num_t(p.size());
      M += M0;
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M << ", " << s0 << ", " << s1 << ", " << M0 << std::endl << std::flush;
  }
  return 0;
}

