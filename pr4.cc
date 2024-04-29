#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <assert.h>
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;

template <typename T> inline T logscale(const T& x) {
  return sgn<T>(x) * log(T(int(1)) + abs(x));
}

template <typename T> inline T expscale(const T& x) {
  return sgn<T>(x) * (exp(abs(x)) - T(int(1)) );
}

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  int rr(8);
  if(argc < 2) std::cerr << argv[0] << " <rand range>? : continue with ";
  if(1 < argc) rr = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << rr << std::endl;
  assert(0 <= rr);
  const int status(24);
  // N.B. if there's prediction apply order algebra, it's up to 4.
  PBond<num_t, P01<num_t> > p0(P01<num_t>(std::max(int(1), std::min(int(4), int(sqrt(num_t(int(status))))))), std::max(int(3), status) + 2);
  PBond<num_t, P01<num_t> > p1(P01<num_t>(std::max(int(1), std::min(int(4), int(sqrt(num_t(int(status))))))), std::max(int(3), status) + 2);
  PBond<num_t, P01<num_t> > p2(P01<num_t>(std::max(int(1), std::min(int(4), int(sqrt(num_t(int(status))))))), std::max(int(3), status) + 2);
  PBond<num_t, P01<num_t> > p3(P01<num_t>(std::max(int(1), std::min(int(4), int(sqrt(num_t(int(status))))))), std::max(int(3), status) + 2);
  PBond<num_t, P0maxRank<num_t> > q(P0maxRank<num_t>(2), int(exp(num_t(2 * 2))) );
  std::string s;
  int   t0(0);
  auto  t1(t0);
  auto  t2(t0);
  auto  t3(t0);
  num_t d(t0);
  auto  s0(t0);
  auto  s1(t0);
  auto  s2(t0);
  auto  s3(t0);
  auto  M0(d);
  auto  M1(d);
  auto  M2(d);
  auto  M3(d);
  auto  MM(d);
  auto  D0(d);
  auto  D1(d);
  auto  D2(d);
  auto  D3(d);
  auto  DM(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    D0 += d;
    D1 += d * M0;
    D2 += d * M0 * M1;
    D3 += d * M0 * M1 * M2;
    DM += logscale<num_t>(logscale<num_t>(d * M0 * M1 * M2 * M3));
    if(! isfinite(DM)) DM = num_t(int(0));
    if(s0 < ++ t0) {
      M0 = p0.next(D0);
      s0 = t0 + arc4random_uniform(rr);
      D0 = num_t(int(0));
      if(s1 < ++ t1) {
        M1 = p1.next(D1);
        s1 = t1 + arc4random_uniform(rr);
        D1 = num_t(int(0));
        if(s2 < ++ t2) {
          M2 = p2.next(D2);
          s2 = t2 + arc4random_uniform(rr);
          D2 = num_t(int(0));
          if(s3 < ++ t3) {
            std::cout << expscale<num_t>(expscale<num_t>(DM * MM)) << ", ";
            M3 = p3.next(D3);
            MM = expscale<num_t>(expscale<num_t>(q.next(DM)));
            s3 = t3 + arc4random_uniform(rr);
            D3 = DM = num_t(int(0));
            std::cout << M0 * M1 * M2 * M3 * MM << std::endl << std::flush;
          }
        }
      }
    }
  }
  return 0;
}

