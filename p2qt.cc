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

template <typename T> static inline pair<T, T> ptry(const SimpleVector<T>& in, vector<pslip_t<T> >& pslip, vector<T>& MM, vector<T>& M2, const int& t) {
  assert(MM.size() == pslip.size() && MM.size() && M2.size() == 4);
  const auto& d(in[in.size() - 1]);
  MM[0] = pSlipJamQuad3<num_t>(in, pslip[0].pipe, pslip[0].lastM,
    pslip[0].shf, pslip[0].nshf, t);
#if defined(_OPENMP)
#pragma omp parallel for schedule(static, 1)
#endif
  for(int i = 1; i < MM.size(); i ++)
    MM[i] = pSlipJamQuad3<num_t>(in, pslip[i].pipe, pslip[i].lastM,
      pslip[i].shf, pslip[i].nshf, t);
  auto lM2(M2);
  // XXX: this makes hard to revert:
  {
    for(int i = 0; i < lM2.size(); i ++) lM2[i] *= d;
  }
  for(int i = 0; i < 4; i ++)
    M2[i] = MM[i];
  for(int i = 4; i < MM.size(); i ++)
    M2[i & 3] += MM[i];
  for(int i = 0; i < 4; i ++)
    M2[i] /= num_t(MM.size() / 4);
  return pSubesube(d, make_pair(lM2, M2), t);
}

int main(int argc, const char* argv[]) {
/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
  std::cout << std::setprecision(30);
  int revertible(- 1);
  if(argc < 2) std::cerr << argv[0] << " <revertible>? : continue with ";
  if(1 < argc) revertible = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << revertible << std::endl;
  vector<pslip_t<num_t> > pslip;
  pslip.reserve(max(1, abs(revertible *= 4)));
  for(int i = 0; i < max(1, abs(revertible)); i ++)
    pslip.emplace_back(pslip_t<num_t>());
  std::string s;
  int   t(0);
  auto  xtr(t);
  num_t d(t);
  auto  M(d);
  vector<num_t> MM;
  idFeeder<num_t> in(0);
  if(revertible < 0) {
    in = idFeeder<num_t>(8);
    for(int i = 0; i < pslip.size(); i ++)
      for(int j = 0; j < pslip[i].pipe.size(); j ++)
        pslip[i].pipe[j] = idFeeder<num_t>(8);
  }
  MM.resize(abs(revertible));
  vector<num_t> M2;
  M2.resize(4, num_t(int(0)));
  idFeeder<num_t> fb(3);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    if(! revertible) {
      std::cout << (M *= d) << ", " << std::flush;
      std::cout <<
        (M = pSlipJamQuad3<num_t>(in.next(d), pslip[0].pipe, pslip[0].lastM,
          pslip[0].shf, pslip[0].nshf, t ++) ) << std::endl << std::flush;
    } else {
      in.next(d);
      if(! in.full) continue;
      auto res(ptry<num_t>(in.res, pslip, MM, M2, t ++));
      const auto& ref(fb.next(res.first)[1]);
      std::cout << (M *= d) << ", " << std::flush;
      if(fb.full) {
        auto inw(in);
        auto pslipw(pslip);
        auto MMM(MM);
        auto MM2(M2);
        const auto nextn(ptry<num_t>(inw.next(- num_t(int(1))), pslipw,
          MMM, MM2, t).first);
        inw    = in;
        pslipw = pslip;
        MMM    = MM;
        MM2    = M2;
        const auto nextp(ptry<num_t>(inw.next(  num_t(int(1))), pslipw,
          MMM, MM2, t).first);
        if((M = sgn<num_t>(abs(ref - nextn) - abs(ref - nextp))) ==
            num_t(int(0)) ) {
          if((M = sgn<num_t>(abs(sgn<num_t>(ref) - nextn) -
            abs(sgn<num_t>(ref) - nextp)) ) == num_t(int(0)) ) {
            // N.B. 2 of the n (mostly greater than 1k) degree equation == 0
            //      condition. (a_0+a_1*x+...+a_n*x^n==0 for pair).
            //      => x*Pi(a'_k-x) == 0 condition but x =={-1,1} satisfiy this.
            //        should we count up a'_k or Sum a'_k (from coefficient)???
            // N.B. instead of them, we add some of the continuity on output
            //      stream from input stream.
            xtr ++;
            M = sgn<num_t>(ref) * res.second;
            
            // N.B. otherwise, M is correct from our shallow test stream.
          }
        }
      }
      std::cout << M << ", " << (t - xtr) << ", " << res.first * fb.res[0] << std::endl << std::flush;
    }
  }
  return 0;
}

