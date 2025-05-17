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
#include <sys/resource.h>

#if defined(_NONLINEAR_X_)
# define _NONLIN_ true
#else
# define _NONLIN_ false
#endif

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
  idFeeder<num_t> p0, p1;
  idFeeder<SimpleVector<num_t> > f0, f1;
  idFeeder<num_t> r0, r1;
  std::string s;
  int   t(0);
  num_t d(t);
  auto  M(d);
  auto  Mp0(d);
  auto  Mp1(d);
  auto  Mq0(d);
  auto  Mq1(d);
  auto  Mr0(d);
  auto  Mr1(d);
  auto  br0(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto dp0(Mp0 * d);
    const auto dq0(Mp0 * Mq0 * d);
    const auto dr0(Mp0 * Mq0 * Mr0 * d);
#if defined(_CHAIN_)
    std::cout << d - M << ", ";
#else
    std::cout << d * M << ", ";
#endif
    Mp0 = pbond<num_t, p0maxNext<num_t>, _NONLIN_>(p0.next(d));
    {
      SimpleVector<num_t> f0n(2);
      f0n[0] = (dp0 + num_t(int(1))) / num_t(int(2));
      f0n[1] = (Mp0 + num_t(int(1))) / num_t(int(2));
      f0.next(std::move(f0n));
    }
#if defined(_NONLINEAR_X_)
    const auto  af0(arctanFeeder<num_t>(f0.res));
#else
    const auto& af0(f0.res);
#endif
    if(9 < af0.size()) {
      Mq0 = (predv0<num_t, 0>(af0.entity, af0.entity.size())[0] + num_t(int(1))) / num_t(int(2));
      Mr0 = pbond<num_t, p012next<num_t>, _NONLIN_>(r0.next(dq0));
      br0 += dr0;
      if((t ++) & 1) {
        br0 /= num_t(int(2));
        const auto dp1(Mp1 * br0);
        const auto dq1(Mp1 * Mq1 * br0);
        Mp1 = pbond<num_t, p0maxNext<num_t>, _NONLIN_>(p1.next(br0));
        {
          SimpleVector<num_t> f1n(2);
          f1n[0] = (dp1 + num_t(int(1))) / num_t(int(2));
          f1n[1] = (Mp1 + num_t(int(1))) / num_t(int(2));
          f1.next(std::move(f1n));
        }
#if defined(_NONLINEAR_X_)
        const auto  af1(arctanFeeder<num_t>(f1.res));
#else
        const auto& af1(f1.res);
#endif
        if(9 < af1.size()) {
          Mq1 = (predv0<num_t, 0>(af1.entity, af1.entity.size())[0] + num_t(int(1))) / num_t(int(2));
          Mr1 = pbond<num_t, p012next<num_t>, _NONLIN_>(r1.next(dq1));
        }
        br0 = num_t(int(0));
      }
    }
    M = Mp0 * Mq0 * Mr0 * Mp1 * Mq1 * Mr1;
    std::cout << (isfinite(M) ? M : M = num_t(int(0)) ) << std::endl << std::flush;
  }
  return 0;
}

