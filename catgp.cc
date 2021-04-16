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
  std::string s;
  assert(3 < argc);
  const auto  range(std::atoi(argv[1]));
  // XXX atof:
  //const num_t rslide(num_t(99) / num_t(100));
  const num_t rslide(std::atof(argv[2]));
  const auto  intensity(- num_t(1) / num_t(8));
  std::vector<P012L<num_t, false> > p;
  std::vector<P012L<num_t, true > > q;
  for(int i = 3; i < argc; i ++) {
    p.emplace_back(P012L<num_t, false>(abs(range), std::atoi(argv[i]), int(num_t(std::atoi(argv[i])) * rslide), intensity));
    q.emplace_back(P012L<num_t, true >(abs(range), std::atoi(argv[i]), int(num_t(std::atoi(argv[i])) * rslide), intensity));
  }
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
      M  = num_t(0);
      for(int i = 0; i < p.size(); i ++)
        M += (range < 0 ? p[i].next(d) : q[i].next(d)) - d;
      M /= num_t(int(p.size()));
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

