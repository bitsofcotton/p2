#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <assert.h>

#if !defined(_FLOAT_BITS_)
  #include <complex>
  #include <cmath>
  using namespace std;
  typedef long double num_t;
  #include <limits>
#else
  #include "ifloat.hh"
  template <typename T> using complex = Complex<T>;
# if _FLOAT_BITS_ == 32
    typedef uint32_t myuint;
    typedef int32_t  myint;
    typedef SimpleFloat<myuint, uint64_t, 32, int64_t> num_t;
    #define mybits 32
# elif _FLOAT_BITS_ == 64
    typedef uint64_t myuint;
    typedef int64_t  myint;
    typedef SimpleFloat<myuint, DUInt<myuint, 64>, 64, int64_t> num_t;
    #define mybits 64
# elif _FLOAT_BITS_ == 128
    typedef DUInt<uint64_t, 64> uint128_t;
    typedef Signed<uint128_t, 128> int128_t;
    typedef uint128_t myuint;
    typedef int128_t  myint;
    typedef SimpleFloat<myuint, DUInt<myuint, 128>, 128, int64_t> num_t;
    #define mybits 128
# else
#   error cannot handle float
# endif
#endif

#include "../p1/simplelin.hh"
#include "../p0/p0.hh"
#include "../p1/p1.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  int eslen(0);
  int vrange(12);
  int ignore(- 4);
  int mul(1);
  int origin(0);
  if(argc < 4) {
    std::cerr << "p1 <extra status> <variable> <ignore> <mul>? <origin>?" << std::endl;
    std::cerr << "continue with p1 " << eslen << " " << vrange << " " << ignore << " " << mul << " " << origin << std::endl;
  } else {
    eslen  = std::atoi(argv[1]);
    vrange = std::atoi(argv[2]);
    ignore = std::atoi(argv[3]);
    if(4 < argc) mul    = std::atoi(argv[4]);
    if(5 < argc) origin = std::atoi(argv[5]);
  }
  const auto ee(eslen < 0 || (1 < argc && argv[1][0] == '-'));
  P0<num_t>  p0;
  P1I<num_t> p(abs(eslen) + abs(ignore), abs(vrange));
  SimpleVector<num_t> buf(abs(vrange) - 1);
  for(int i = 0; i < buf.size(); i ++)
    buf[i] = num_t(0);
  std::string s;
  num_t d(0);
  auto  d0(d);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  s3(d);
  auto  s4(d);
  int   t2(0);
  auto  t3(t2);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    d *= num_t(mul);
    if(ee) {
      if(d0 == num_t(0)) d0 = d;
      d = atan(d - d0);
    }
    const auto delta(vrange < 0 ? atan(d - bd) : d - bd);
    if(d != bd) {
      if(bd != num_t(0) && M != num_t(0)) {
        t2 ++; t3 ++;
        s0 += delta * M * num_t(t2 - t3);
        s1 += delta - M;
        s2 += delta * M * num_t(t2);
        s3 -= delta * M * num_t(t3);
        s4 += delta * M;
      }
      for(int i = 0; i < buf.size() - 1; i ++)
        buf[i] = buf[i + 1];
      p.next(buf[buf.size() - 1] = delta, - ignore, num_t(origin));
      if(p.invariant.size()) {
        auto avg(p.invariant[0]);
        for(int i = 1; i < p.invariant.size(); i ++)
          avg += p.invariant[i];
        auto pp(p0.next(abs(vrange) - 1));
        auto qq(pp);
        for(int i = 0; i < qq.size(); i ++)
          qq[i] = avg[i];
        const auto nq(sqrt(qq.dot(qq)));
        const auto C(avg[abs(vrange)] / sqrt(num_t((abs(eslen) + abs(vrange) - 1) * 2 + 1) * num_t(abs(vrange) + 1)) / nq);
        qq /= nq;
        const auto pq(pp - qq * pp.dot(qq));
        const auto npq(sqrt(pq.dot(pq)));
        M = (pq.dot(buf) + pp.dot(qq) * (C - num_t(origin) / nq * avg[abs(vrange) - 1])) / npq;
      }
      if(! isfinite(M) || isnan(M)) M = num_t(0);
      if(0 < s2) s2 = num_t(t2 = 0);
      if(0 < s3) s3 = num_t(t3 = 0);
    }
    std::cout << M << ", " << s0 << ", " << s1 << ", " << s4 << std::endl << std::flush;
  }
  return 0;
}

