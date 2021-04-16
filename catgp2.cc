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
  assert(4 < argc);
  const auto  range(std::atoi(argv[1]));
  // XXX atof:
  //const num_t rslide(num_t(99) / num_t(100));
  const num_t rslide(std::atof(argv[3]));
  const auto  intensity(- num_t(1) / num_t(8));
  std::vector<std::vector<P012L<num_t, false> > > p;
  std::vector<std::vector<P012L<num_t, true > > > q;
  {
    std::vector<P012L<num_t, false> > pp;
    std::vector<P012L<num_t, true > > qq;
    for(int i = 4; i < argc; i ++) {
      pp.emplace_back(P012L<num_t, false>(abs(range), std::atoi(argv[i]), int(num_t(std::atoi(argv[i])) * rslide), intensity));
      qq.emplace_back(P012L<num_t, true >(abs(range), std::atoi(argv[i]), int(num_t(std::atoi(argv[i])) * rslide), intensity));
     }
     p.resize(std::atoi(argv[2]), pp);
     q.resize(std::atoi(argv[2]), qq);
  }
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  M0(d);
  std::vector<num_t> dd(p.size(), num_t(0));
  auto  rr(dd);
  auto  M(rr);
  {
    std::getline(std::cin, s, '\n');
    std::stringstream ins(s);
    ins >> dd[0];
    for(int i = 1; i < dd.size(); i ++)
      dd[i] = dd[0];
  }
  while(std::getline(std::cin, s, '\n')) {
    const auto bd0(d);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd0) {
      if(bd0 != num_t(0) && M0 != num_t(0)) {
        s0 += (d - bd0) - M0;
        s1 += (d - bd0) * M0;
      }
      const auto bd(dd);
      for(int i = 0; i < p.size(); i ++) {
        dd[i] += (d - bd0) * rr[i];
        const auto bf(M[i] * (dd[i] - bd[i]));
        rr[i] += num_t(int(arc4random_uniform(0x10000) + arc4random_uniform(0x10000) - 0x8000 * 2)) / num_t(int(0x8000));
        if(dd[i] != num_t(0)) {
          M[i] = num_t(0);
          for(int j = 0; j < p[i].size(); j ++)
            M[i] += (range < 0 ? p[i][j].next(dd[i]) : q[i][j].next(dd[i])) - dd[i];
          M0  += (M[i] /= num_t(int(p[i].size()))) * bf * rr[i];
        }
      }
      M0 /= num_t(int(p.size()));
      if(! isfinite(M0) || isnan(M0)) M0 = num_t(0);
    }
    std::cout << M0 << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

