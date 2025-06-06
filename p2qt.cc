#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <assert.h>
#include <random>
#include <sys/resource.h>

/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
#include "lieonn.hh"
typedef myfloat num_t;
/*
#if defined(_FLOAT_BITS_)
#undef int
#endif
*/

int main(int argc, const char* argv[]) {
/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
  std::cout << std::setprecision(30);
  int revertible(0);
  if(argc < 2) std::cerr << argv[0] << " <revertible>? : continue with ";
  if(1 < argc) revertible = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << revertible << std::endl;
  assert(0 <= revertible);
  vector<pslip_t<num_t> > pslip;
  pslip.reserve(max(1, revertible *= 4));
  for(int i = 0; i < max(1, revertible); i ++)
    pslip.emplace_back(pslip_t<num_t>());
  std::string s;
  int   t(0);
  num_t d(t);
  auto  M(d);
  vector<num_t> MM;
  idFeeder<num_t> in(0);
  MM.resize(revertible);
  vector<num_t> M2;
  M2.resize(4, num_t(int(0)));
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    if(! revertible) {
      std::cout << (M *= d) << ", " << std::flush;
      std::cout <<
        (M = pSlipJamQuad3<num_t>(in.next(d), pslip[0].pipe, pslip[0].lastM,
          pslip[0].shf, pslip[0].nshf, t ++) ) << std::endl << std::flush;
    } else {
      MM[0] = pSlipJamQuad3<num_t>(in.next(d), pslip[0].pipe, pslip[0].lastM,
        pslip[0].shf, pslip[0].nshf, t);
#if defined(_OPENMP)
#pragma omp parallel for schedule(static, 1)
#endif
      for(int i = 1; i < MM.size(); i ++)
        MM[i] = pSlipJamQuad3<num_t>(in.next(d), pslip[i].pipe, pslip[i].lastM,
          pslip[i].shf, pslip[i].nshf, t);
      assert(M2.size() == 4);
      auto lM2(M2);
      // XXX: this makes hard to revert:
      for(int i = 0; i < lM2.size(); i ++) lM2[i] *= d;
      for(int i = 0; i < 4; i ++)
        M2[i] = MM[i];
      for(int i = 4; i < MM.size(); i ++)
        M2[i & 3] += MM[i];
      for(int i = 0; i < 4; i ++)
        M2[i] /= num_t(MM.size() / 4);
      auto res(pSubesube(d, make_pair(lM2, M2), t ++));
      std::cout << res.first << ", " << res.second << std::endl;
    }
  }
  return 0;
}

