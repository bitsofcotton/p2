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
  const int   vrange(2);
        int   stat(200);
        num_t inten(- num_t(1));
        int   comp(- 8);
  if(argc < 4)
    std::cerr << "catgp <condition>? <intensity>? <complexity>?" << std::endl;
  else {
    if(1 < argc) stat  = std::atoi(argv[1]);
    // XXX: atof
    if(2 < argc) inten = std::atof(argv[2]);
    if(3 < argc) comp  = std::atoi(argv[3]);
  }
  std::cerr << "continue with catgp " << stat << " " << inten << " " << comp << std::endl;
  P012L<num_t, false> p(vrange, stat, comp, inten);
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
      M = p.next(d) - d;
      if(! isfinite(M) || isnan(M)) M = num_t(0);
    }
    std::cout << M << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

